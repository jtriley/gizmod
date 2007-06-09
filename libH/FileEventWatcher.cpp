    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  FileEventWatcher.cpp
*** \brief FileEventWatcher class body
***
*****************************************
  *****************************************
    **/

/*
  
  Copyright (c) 2007, Tim Burrell
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
*/

#include "FileEventWatcher.hpp"
#include "Debug.hpp"
#include "Exception.hpp"
#include "Util.hpp"
#include "UtilTime.hpp"
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs / Defines
///////////////////////////////////////

/**
 * \def   READ_BUF_SIZE 
 * \brief Default size of the read buffer for the automatic file reader
 */
#define READ_BUF_SIZE		65536

/**
 * \def   NOTIFY_EVENT_SIZE	
 * \brief Human friendly size of the inotify_event struct
 */
#define NOTIFY_EVENT_SIZE	(sizeof(struct inotify_event))

/**
 * \def   NOTIFY_READ_BUF_SIZE 
 * \brief Default size of the inotify read buffer for the automatic file reader
 */
#define NOTIFY_READ_BUF_SIZE	1024 * (NOTIFY_EVENT_SIZE + 16)

/**
 * \def   DEVICE_NAME_BUF_SIZE
 * \brief Default size of the device name buffer
 */
#define DEVICE_NAME_BUF_SIZE	1024

/**
 * \def   RETRY_FAIL_WAIT_NSECS
 * \brief Amount of nanoseconds to wait on an open of a new device before retrying
 */
#define RETRY_FAIL_WAIT_NSECS	100000000

/**
 * \def   MAX_RETRIES
 * \brief Maximum number of retries when opening a new device
 */
#define MAX_RETRIES		5

/**
 * \def    POLL_TIMEOUT
 * \brief  Poll timeout in milliseconds
 */
#define POLL_TIMEOUT	1000

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief DeviceInfo Default Constructor
 */
DeviceInfo::DeviceInfo() {
	DeviceIDBusType = -1;
	DeviceIDProduct = -1;
	DeviceIDVendor = -1;
	DeviceIDVersion = -1;	
}

/**
 * \brief DeviceInfo Init Constructor
 */
DeviceInfo::DeviceInfo(std::string deviceName, std::string fileName, int deviceIDBusType, int deviceIDVendor, int deviceIDProduct, int deviceIDVersion, int fileDescriptor) {
	DeviceName = deviceName;
	FileName = fileName;
	DeviceIDBusType = deviceIDBusType;
	DeviceIDVendor = deviceIDVendor;
	DeviceIDProduct = deviceIDProduct;
	DeviceIDVersion = deviceIDVersion;
	FileDescriptor = fileDescriptor;
}

/**
 * \brief DeviceInfo Init Constructor
 */
DeviceInfo::DeviceInfo(const DeviceInfo & DeviceInformation) {
	DeviceName = DeviceInformation.DeviceName;
	FileName = DeviceInformation.FileName;
	DeviceIDBusType = DeviceInformation.DeviceIDBusType;
	DeviceIDVendor = DeviceInformation.DeviceIDVendor;
	DeviceIDProduct = DeviceInformation.DeviceIDProduct;
	DeviceIDVersion = DeviceInformation.DeviceIDVersion;
	FileDescriptor = DeviceInformation.FileDescriptor;
}

/**
 * \brief DeviceInfo Destructor
 */
DeviceInfo::~DeviceInfo() {
}

/**
 * \brief FileEventWatcher Default Constructor
 */
FileEventWatcher::FileEventWatcher() {
	mPolling = false;
	if ((mInotifyFD = inotify_init()) < 0)
		throw H::Exception("Failed to Initialize Inotify!", __FILE__, __FUNCTION__, __LINE__);	
}

/**
 * \brief FileEventWatcher Destructor
 */
FileEventWatcher::~FileEventWatcher() {
	removeAllWatchDescriptors();
	if (mInotifyFD != -1)
		close(mInotifyFD);
}

/**
 * \brief FileWatchee Default Constructor
 */
FileWatchee::FileWatchee() {
	WatchType = WATCH_IN;
	fd = -1;
	Events = POLLIN;
}

/**
 * \brief FileWatchee Init Constructor
 */
FileWatchee::FileWatchee(std::string fileName, FileWatchType watchType, short events, int fileDescriptor, int watchDescriptor, std::string deviceName, int deviceIDBusType, int deviceIDVendor, int deviceIDProduct, int deviceIDVersion) :
	DeviceInfo(deviceName, fileName, deviceIDBusType, deviceIDVendor, deviceIDProduct, deviceIDVersion, fileDescriptor)
{
	WatchType = watchType;
	Events = events;
	fd = fileDescriptor;
	wd = watchDescriptor;
	if (fd < 0)
		DeviceType = WATCH_INOTIFY;
	else
		DeviceType = WATCH_POLL;
}

/**
 * \brief FileWatchee Destructor
 */
FileWatchee::~FileWatchee() {
	if (fd > -1)
		close(fd);
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Add a file to watch for events
 * \param FileName Absolute path of the file to watch
 * \param WatchType Type of watch to perform on the file
 * \param DefaultDeviceName Default device name if the device does not support having a name
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::addFileToWatch(std::string FileName, FileWatchType WatchType, std::string DefaultDeviceName) {
	// make sure we're not already watching this file
	shared_ptr<FileWatchee> pDupWatchee = getWatcheeByPath(FileName);
	if (pDupWatchee) {
		cdbg << "Already Watching File [" << FileName << "]" << endl;
		return shared_ptr<FileWatchee>();
	}
	pDupWatchee.reset();
	cdbg1 << "Adding File [" << FileName << "] to Watch List with Mode [" << WatchType << "]" << endl;
	
	// get mode mask
	int 	flags = 0;
	string 	ModeString;
	short	events = 0;
	switch (WatchType) {
	case WATCH_IN:
		flags = O_RDONLY;
		events = POLLIN;
		ModeString = "Read";
		break;
	case WATCH_OUT:
		flags = O_WRONLY;
		events = POLLOUT;
		ModeString = "Write";
		break;
	case WATCH_INOUT:
		flags = O_RDWR;
		events = POLLIN | POLLOUT;
		ModeString = "Read / Write";
		break;
	case WATCH_INVALID:
		throw H::Exception("Invalid Watch Type specified on [" + FileName + "]", __FILE__, __FUNCTION__, __LINE__);
	}
	
	// make sure it exists
	filesystem::path FilePath(FileName);
	if (!filesystem::exists(FilePath))
		throw H::Exception("Path [" + FileName + "] does not exist, or cannot open (perms?) with Mode [" + ModeString + "]", __FILE__, __FUNCTION__, __LINE__);
	
	// if it's a directory, then watch with inotify, otherwise use poll
	int fd = -1;
	int wd = -1;
	char DeviceName[DEVICE_NAME_BUF_SIZE] = {'\0'};
	unsigned short DeviceIDs[4] = {-1, -1, -1, -1};
	if (filesystem::is_directory(FilePath)) {
		// directory, add watch
		if ((wd = inotify_add_watch(mInotifyFD, FileName.c_str(), IN_CREATE | IN_DELETE | IN_DELETE_SELF)) == -1)
			throw H::Exception("Failed to add Watch on Directory [" + FileName + "]", __FILE__, __FUNCTION__, __LINE__);
		fd = -wd;
		mInotifyWDs.push_back(wd);
		strcpy(DeviceName, "Directory");
	} else {	
		// not a directory, open the device
		int retry;
		for (retry = 0; retry < MAX_RETRIES; retry ++) {
			if ((fd = open(FileName.c_str(), flags)) == -1) {
				cdbg1 << "New Device [" << FileName << "] Open Failed -- Retrying" << endl;
				UtilTime::nanoSleep(RETRY_FAIL_WAIT_NSECS);
				continue;
			}
			break;
		}
		if (retry == MAX_RETRIES) {
			//throw H::Exception("Failed to Open file [" + FileName + "] with Mode [" + ModeString + "]", __FILE__, __FUNCTION__, __LINE__);
			cerr << "Failed to Open [" << FileName << "] for [" << ModeString + "] -- Check Permissions!" << endl;
			return shared_ptr<FileWatchee>();
		}
		
		// get the device name
		if (ioctl(fd, EVIOCGNAME(sizeof(DeviceName)), DeviceName) < 0) {
			cdbg3 << "Failed to Get Device Name for [" + FileName + "]" << endl;
			strcpy(DeviceName, DefaultDeviceName.c_str());
		}
		
		// get the device id information
		if (ioctl(fd, EVIOCGID, DeviceIDs) < 0)
			cdbg3 << "Failed to Get Device IDs for [" + FileName + "]" << endl;			
	}
	
	cdbg1 << "Watching Device [" << FileName << "]: " << DeviceName << endl;
	shared_ptr<FileWatchee> pWatchee(new FileWatchee(FileName, WatchType, events, fd, wd, DeviceName, DeviceIDs[0], DeviceIDs[1], DeviceIDs[2], DeviceIDs[3]));
	mWatchees.insert(make_pair(fd, pWatchee));
	buildPollFDArrayFromWatchees();
	onFileEventRegister(pWatchee);
			
	return pWatchee;
}

/**
 * \brief Add a unix socket to watch for events
 * \param FileName Absolute path of the file to watch
 * \param DeviceName Device name
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::addUnixSocketToWatch(std::string FileName, std::string DeviceName) {
	// get mode mask
	string	 	ModeString = "Read";
	short		events = POLLIN;
	FileWatchType 	WatchType = WATCH_IN;
	
	// make sure it exists
	filesystem::path FilePath(FileName);
	if (!filesystem::exists(FilePath))
		throw H::Exception("Path [" + FileName + "] does not exist, or cannot open (perms?) with Mode [" + ModeString + "]", __FILE__, __FUNCTION__, __LINE__);
	
	// set up the datastructure
	struct sockaddr_un Addr;
	Addr.sun_family = AF_UNIX;
	strcpy(Addr.sun_path, FileName.c_str());
	
	// open the unix socket
	int fd;
	if ((fd = socket(AF_UNIX,SOCK_STREAM, 0)) == -1) {
		cdbg1 << "Failed to Creat Socket for [" << FileName << "] for [" << ModeString + "] -- Check Permissions!" << endl;
		return shared_ptr<FileWatchee>();
	}
	
	// connect to the socket
	if (connect(fd,(struct sockaddr *) &Addr,sizeof(Addr)) == -1)  {
		cdbg1 << "Failed to Connect to [" << FileName << "] for [" << ModeString + "] -- Check Permissions!" << endl;
		close(fd);
		return shared_ptr<FileWatchee>();
	}
	
	cdbg1 << "Watching Unix Socket [" << FileName << "]: " << DeviceName << endl;
	shared_ptr<FileWatchee> pWatchee(new FileWatchee(FileName, WatchType, events, fd, -1, DeviceName, -1, -1, -1, -1));
	mWatchees.insert(make_pair(fd, pWatchee));
	buildPollFDArrayFromWatchees();
	onFileEventRegister(pWatchee);
			
	return pWatchee;
}

/**
 * \brief  Build the mPollFDs array from the list of watchees
 */
void FileEventWatcher::buildPollFDArrayFromWatchees() {
	// clear out the pollfsd
	mPollFDs.clear();
	
	// put in the inotify pollfd
	struct pollfd PollFD;
	PollFD.fd = mInotifyFD;
	PollFD.events = POLLIN | POLLOUT;
	PollFD.revents = 0;
	mPollFDs.push_back(PollFD);
	
	// build the rest of the pollfds via the functor
	apply_func(mWatchees, &FileEventWatcher::buildPollFDArrayFunctor, this);
}

/**
 * \brief Functor for building the array of mPollFDs
 * \param pWatchee The Watchee
 */
void FileEventWatcher::buildPollFDArrayFunctor(std::pair< int, boost::shared_ptr<FileWatchee> > WatcheePair) {
	boost::shared_ptr<FileWatchee> pWatchee = WatcheePair.second;
	if ( (!pWatchee) || (pWatchee->fd < 0) )
		return;
	
	// Add the new watchee to the list
	struct pollfd PollFD;
	PollFD.fd = pWatchee->fd;
	PollFD.events = pWatchee->Events;
	PollFD.revents = 0;
	mPollFDs.push_back(PollFD);
}

/**
 * \brief  Get the type of the file event
 * \param  Index The index of the file to check
 * \return Type of the event (FileWatchType)
 */
FileWatchType FileEventWatcher::getType(int Index) {
	if (mPollFDs[Index].revents & POLLIN)
		return WATCH_IN;
	else if (mPollFDs[Index].revents & POLLOUT)
		return WATCH_OUT;
	else if (mPollFDs[Index].revents & POLLOUT & POLLIN)
		return WATCH_INOUT;
	else
		return WATCH_INVALID;
}

/**
 * \brief  Get a Watchee by its file descriptor
 * \param  fd File Desriptor of the desired watchee
 * \return The watchee (shared_ptr to FileWatchee)
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::getWatcheeByFileDescriptor(int fd) {
	return mWatchees[fd];
}

/**
 * \brief  Get a Watchee by its file name
 * \param  FileName File name of watchee to get
 * \return The watchee (shared_ptr to FileWatchee)
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::getWatcheeByPath(std::string FileName) {
	map< int, shared_ptr<FileWatchee> >::iterator iter;
	for (iter = mWatchees.begin(); iter != mWatchees.end(); iter ++) {
		shared_ptr<FileWatchee> pWatchee = iter->second;
		if (!pWatchee) {
			mWatchees.erase(iter);
			continue;
		}
		if (pWatchee->FileName == FileName)
			return pWatchee;
	}
	
	// not found, return null shared pointer
	return shared_ptr<FileWatchee>();
}

/**
 * \brief  Get a Watchee by its watch descriptor
 * \param  wd Watch Desriptor of the desired watchee
 * \return The watchee (shared_ptr to FileWatchee)
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::getWatcheeByWatchDescriptor(int wd) {
	return mWatchees[-wd];
}

/**
 * \brief  Read the input event waiting on a file descriptor
 * \param  fd The file descriptor
 * \param  Buffer The buffer to place contents into
 */
void FileEventWatcher::readFromFile(int fd, DynamicBuffer<char> & Buffer) {
	char ReadBuffer[READ_BUF_SIZE];
	ssize_t BytesRead;
	do {
		if ((BytesRead = read(fd, ReadBuffer, READ_BUF_SIZE)) <= 0)
			throw H::DeviceDisconnectException();
		Buffer.addToBuffer(ReadBuffer, BytesRead);
	} while (BytesRead == READ_BUF_SIZE);
}

/**
 * \brief Functor that checks for and handles events on a pollfd object
 * \param item The item to check and handle events for
 */
void FileEventWatcher::handleEventsOnFile(struct pollfd & item) {
	if (item.fd == mInotifyFD) {
		if (item.revents & POLLERR) {
			cdbg << "Error detected on inotify device" << endl;
		} else if ( (item.revents & POLLIN) || (item.revents & POLLPRI) ) {
			// read from the inotify device
			char ReadBuffer[NOTIFY_READ_BUF_SIZE];
			int BytesRead = read(mInotifyFD, ReadBuffer, NOTIFY_READ_BUF_SIZE);
			if (BytesRead < 0)
				if (errno == EINTR)
					return;
				else
					throw H::Exception("Failed to Read from Inotify Device!", __FILE__, __FUNCTION__, __LINE__);
				
			// loop through all of the returned inotify_event structures and produce events
			int BytesHandled = 0;
			while (BytesHandled < BytesRead) {
				struct inotify_event * event;
				event = (struct inotify_event *) &ReadBuffer[BytesHandled];
				BytesHandled += NOTIFY_EVENT_SIZE + event->len;
				
				shared_ptr<FileWatchee> pWatchee = getWatcheeByWatchDescriptor(event->wd);
				if (!pWatchee) {
					cerr << "Unhandled inotify event: " << event->name << endl;
					continue;
				}
				
				if (event->mask & IN_ACCESS)
					cout << "Access" << endl;
				if (event->mask & IN_ATTRIB)
					cout << "Attrib" << endl;
				if (event->mask & IN_CLOSE_WRITE)
					cout << "CloseWrite" << endl;
				if (event->mask & IN_CLOSE_NOWRITE)
					cout << "CloseNoWrite" << endl;
				if (event->mask & IN_CREATE)
					onFileEventCreate(pWatchee, pWatchee->FileName + "/" + event->name, event->name);
				if ( (event->mask & IN_DELETE) || (event->mask & IN_DELETE_SELF) ) {
					// pass in the actual watchee rather than the directory watchee
					shared_ptr<FileWatchee> pActualWatchee = getWatcheeByPath(pWatchee->FileName + "/" + event->name);
					if (!pActualWatchee) {
						cdbg2 << "Delete inotify event on unhandled file: " << event->name << endl;
						continue;
					}
					onFileEventDelete(pActualWatchee, pActualWatchee->FileName, event->name);
				}
				if (event->mask & IN_MODIFY)
					cout << "Modify" << endl;
				if (event->mask & IN_MOVE_SELF)
					cout << "MoveSelf" << endl;
				if (event->mask & IN_MOVED_FROM)
					cout << "MovedFrom" << endl;
				if (event->mask & IN_MOVED_TO)
					cout << "MovedTo" << endl;
				if (event->mask & IN_OPEN)
					cout << "Open" << endl;
				if (event->mask & IN_UNMOUNT)
					cout << "Unmount" << endl;
			}
		}
	} else if (item.fd >= 0) {
		if (item.revents & POLLERR) {
			shared_ptr<FileWatchee> pWatchee = getWatcheeByFileDescriptor(item.fd);
			if (pWatchee) {
				cdbg5 << "Error detected on poll device: " << item.fd << " -- " << pWatchee->FileName << endl;
				onFileEventDisconnect(pWatchee);
				removeWatchee(pWatchee);			
			} else {
				cdbg5 << "Error detected on poll device: " << item.fd << endl;
				buildPollFDArrayFromWatchees();
			}
		} else if ( (item.revents & POLLIN) || (item.revents & POLLPRI) ) {
			// poll device, try to read from it
			shared_ptr<FileWatchee> pWatchee = getWatcheeByFileDescriptor(item.fd);
			if (!pWatchee) {
				cdbg5 << "Unhandled file event on fd [" << item.fd << "]" << endl;
				buildPollFDArrayFromWatchees();
				return;
			}
			try {
				DynamicBuffer<char> Buffer;
				readFromFile(item.fd, Buffer);
				if (pWatchee)
					onFileEventRead(pWatchee, Buffer);
			} catch (H::DeviceDisconnectException & e) {
				if ( (pWatchee) && (pWatchee->DeviceType == WATCH_POLL) ) {
					onFileEventDisconnect(pWatchee);
					removeWatchee(pWatchee);
				} else
					cout << "Disconnect from Unknown Device" << endl;
			}			
		}
	}
}

/**
 * \brief Event triggered when a new file is created
 * \param pWatchee The Watchee that triggered the event
 * \param FullPath The full (absolute) path of the new file
 * \param FileName The file name (relative ) of the new file
 */
void FileEventWatcher::onFileEventCreate(boost::shared_ptr<FileWatchee> pWatchee, std::string FullPath, std::string FileName) {
	// override me
}

/**
 * \brief Event triggered when a file is deleted
 * \param pWatchee The Watchee that triggered the event
 * \param FullPath The full (absolute) path of the new file
 * \param FileName The file name (relative ) of the new file
 */
void FileEventWatcher::onFileEventDelete(boost::shared_ptr<FileWatchee> pWatchee, std::string FullPath, std::string FileName) {
	// override me
}

/**
 * \brief Event triggered when a file is disconnected
 * \param pWatchee The Watchee that triggered the event
 */
void FileEventWatcher::onFileEventDisconnect(boost::shared_ptr<FileWatchee> pWatchee) {
	// override me
}

/**
 * \brief Event triggered when data is waiting on a device
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void FileEventWatcher::onFileEventRead(boost::shared_ptr<FileWatchee> pWatchee, DynamicBuffer<char> const & ReadBuffer) {
	// override me
}

/**
 * \brief Event triggered when a new device is registered
 * \param pWatchee The Watchee that triggered the event
 */
void FileEventWatcher::onFileEventRegister(boost::shared_ptr<FileWatchee> pWatchee) {
	// override me
}

/**
 * \brief Event called when the class will begin watching for events (and blocking)
 */
void FileEventWatcher::onFileEventWatchBegin() {
	// override me
}

/**
 * \brief Event called when the class has ended watching for events (and done blocking)
 */
void FileEventWatcher::onFileEventWatchEnd() {
	// override me
}

/**
 * \brief Unregister a watch descriptor with inotify
 * \param wd The watch descriptor
 */
void FileEventWatcher::removeWatchDescriptor(int wd) {
	inotify_rm_watch(mInotifyFD, wd);
}

/**
 * \brief Remove all watch descriptors
 */
void FileEventWatcher::removeAllWatchDescriptors() {
	apply_func(mInotifyWDs, &FileEventWatcher::removeWatchDescriptor, this);
}

/**
 * \brief Remove a watchee from the watch list
 * \param pWatchee The watchee to remove
 */
void FileEventWatcher::removeWatchee(boost::shared_ptr<FileWatchee> pWatchee) {
	if (!pWatchee)
		return;
	map< int, shared_ptr<FileWatchee> >::iterator iter;
	bool removed = false;
	for (iter = mWatchees.begin(); iter != mWatchees.end(); iter ++) {
		if (!iter->second)
			continue;
		if (iter->second->fd == pWatchee->fd) {
			cdbg4 << "Removed Watchee [" << pWatchee->FileName << "]" << endl;
			mWatchees.erase(iter);
			removed = true;
			break;
		}
	}
	if (removed)
		buildPollFDArrayFromWatchees();
}

/**
 * \brief Stop watching for file events
 * 
 * This does not interrupt a current call to poll, so watchForFileEvents will only
 * exit after this function is called, and then the next event is received
 */
void FileEventWatcher::shutdown() {
	mPolling = false;
}

/**
 * \brief Watch for file events on already specified files
 *
 * Note: Blocking
 */
void FileEventWatcher::watchForFileEvents() {
	if (mPollFDs.size() == 0) {
		cdbg << "FileEventWatcher :: watchForFileEvents -- No file to watch!" << endl;
		return;
	}
		
	// fire notification of blocking
	onFileEventWatchBegin();
	
	cdbg1 << "FileEventWatcher :: Watching [" << (int) mPollFDs.size() << " Files] for Events..." << endl;
	mPolling = true;
	int ret;
	do {	
		// poll the open files
		if ((ret = poll(&mPollFDs[0], mPollFDs.size(), POLL_TIMEOUT)) == -1) {
			// error
			cdbg1 << "Poll error: " << strerror(errno) << endl;
			//continue; // <-- for debugging, since the debugger fires signals and causes poll to abort
			
			// fire notification of end of blocking
			onFileEventWatchEnd();
			return;
		}

		if (!ret)
			// timeout
			continue;
		
		// file events have happened, check for them and dispatch
		cdbg5 << "Processing File Events..." << endl;
		apply_func(mPollFDs, &FileEventWatcher::handleEventsOnFile, this);
	} while (mPolling);
	cdbg1 << "FileEventWatcher :: Done Watching for File Events" << endl;
	
	// fire notification of end of blocking
	onFileEventWatchEnd();
}
