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
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>

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

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

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
FileWatchee::FileWatchee(std::string fileName, FileWatchType watchType, short events, int fileDescriptor, int watchDescriptor, std::string deviceName) {
	FileName = fileName;
	WatchType = watchType;
	Events = events;
	fd = fileDescriptor;
	wd = watchDescriptor;
	if (fd == -1)
		DeviceType = WATCH_INOTIFY;
	else
		DeviceType = WATCH_POLL;
	DeviceName = deviceName;
}

/**
 * \brief FileWatchee Destructor
 */
FileWatchee::~FileWatchee() {
	if (fd != -1)
		close(fd);
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Add a file to watch for events
 * \param FileName Absolute path of the file to watch
 * \param WatchType Type of watch to perform on the file
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::addFileToWatch(std::string FileName, FileWatchType WatchType) {
	// make sure we're not already watching this file
	shared_ptr<FileWatchee> pDupWatchee = getWatcheeByPath(FileName);
	if (pDupWatchee) {
		cdbg << "Already Watching File [" << FileName << "]" << endl;
		return shared_ptr<FileWatchee>();
	}
	pDupWatchee.reset();
	cdbg1 << "Adding File [" << FileName << "] to Watch List with Mode [" << WatchType << "]" << endl;
	
	// get mode mask
	int 	flags;
	string 	ModeString;
	short	events;
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
	if (filesystem::is_directory(FilePath)) {
		// directory, add watch
		if ((wd = inotify_add_watch(mInotifyFD, FileName.c_str(), IN_CREATE | IN_DELETE | IN_DELETE_SELF)) == -1)
			throw H::Exception("Failed to add Watch on Directory [" + FileName + "]", __FILE__, __FUNCTION__, __LINE__);
		mInotifyWDs.push_back(wd);
		strcpy(DeviceName, "Directory");
	} else {	
		// not a directory, open the device
		if ((fd = open(FileName.c_str(), flags)) == -1)
			throw H::Exception("Failed to Open file [" + FileName + "] with Mode [" + ModeString + "]", __FILE__, __FUNCTION__, __LINE__);
		
		// get the device name
		if (ioctl(fd, EVIOCGNAME(sizeof(DeviceName)), DeviceName) < 0)
			throw H::Exception("Failed to Get Device Name for [" + FileName + "]", __FILE__, __FUNCTION__, __LINE__);
	}
	
	cdbg << "Watching Device [" << FileName << "]: " << DeviceName << endl;
	shared_ptr<FileWatchee> pWatchee(new FileWatchee(FileName, WatchType, events, fd, wd, DeviceName));
	mWatchees.push_back(pWatchee);
	buildPollFDArrayFromWatchees();
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
void FileEventWatcher::buildPollFDArrayFunctor(boost::shared_ptr<FileWatchee> pWatchee) {
	if (pWatchee->fd == -1)
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
	list< shared_ptr<FileWatchee> >::iterator iter;
	for (iter = mWatchees.begin(); iter != mWatchees.end(); iter ++) {
		if ((*iter)->fd == fd)
			return *iter;
	}
	// not found, return null shared pointer
	return shared_ptr<FileWatchee>();
}

/**
 * \brief  Get a Watchee by its file name
 * \param  FileName File name of watchee to get
 * \return The watchee (shared_ptr to FileWatchee)
 */
boost::shared_ptr<FileWatchee> FileEventWatcher::getWatcheeByPath(std::string FileName) {
	list< shared_ptr<FileWatchee> >::iterator iter;
	for (iter = mWatchees.begin(); iter != mWatchees.end(); iter ++) {
		if ((*iter)->FileName == FileName)
			return *iter;
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
	list< shared_ptr<FileWatchee> >::iterator iter;
	for (iter = mWatchees.begin(); iter != mWatchees.end(); iter ++) {
		if ((*iter)->wd == wd)
			return *iter;
	}
	// not found, return null shared pointer
	return shared_ptr<FileWatchee>();
}

/**
 * \brief  Read the input event waiting on a file descriptor
 * \param  fd The file descriptor
 * \return The results of the read (DynamicBuffer)
 */
shared_ptr< DynamicBuffer<char> > FileEventWatcher::readFromFile(int fd) {
	shared_ptr< DynamicBuffer<char> > pBuffer(new DynamicBuffer<char>);
	
	char ReadBuffer[READ_BUF_SIZE];
	ssize_t BytesRead;
	do {
		if ((BytesRead = read(fd, ReadBuffer, READ_BUF_SIZE)) <= 0)
			throw H::DeviceDisconnectException();
		pBuffer->addToBuffer(ReadBuffer, BytesRead);
	} while (BytesRead == READ_BUF_SIZE);
	
	return pBuffer;
}

/**
 * \brief Remove all watch descriptors
 */
void FileEventWatcher::removeAllWatchDescriptors() {
	apply_func(mInotifyWDs, &FileEventWatcher::removeWatchDescriptor, this);
}

/**
 * \brief Unregister a watch descriptor with inotify
 * \param wd The watch descriptor
 */
void FileEventWatcher::removeWatchDescriptor(int wd) {
	inotify_rm_watch(mInotifyFD, wd);
}

/**
 * \brief Functor that checks for and handles events on a pollfd object
 * \param item The item to check and handle events for
 */
void FileEventWatcher::handleEventsOnFile(struct pollfd & item) {
	if (item.fd == mInotifyFD) {
		if (item.revents & POLLIN) {			
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
				if (event->mask & IN_DELETE)
					onFileEventDelete(pWatchee, pWatchee->FileName + "/" + event->name, event->name);
				if (event->mask & IN_DELETE_SELF)
					onFileEventDelete(pWatchee, pWatchee->FileName + "/" + event->name, event->name);
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
	} else {
		if (item.revents & POLLIN) {
			// poll device, try to read from it
			shared_ptr<FileWatchee> pWatchee = getWatcheeByFileDescriptor(item.fd);
			if (!pWatchee)
				cerr << "Unhandled file event on fd [" << item.fd << "]" << endl;
			try {
				shared_ptr< DynamicBuffer<char> > pBuffer = readFromFile(item.fd);
				if (pWatchee)
					cdbg << "Event Detected on Device [" << pWatchee->DeviceName << "]" << endl;
			} catch (H::DeviceDisconnectException & e) {
				if (pWatchee) {
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
 * \brief Remove a watchee from the watch list
 * \param pWatchee The watchee to remove
 */
void FileEventWatcher::removeWatchee(boost::shared_ptr<FileWatchee> pWatchee) {
	list< shared_ptr<FileWatchee> >::iterator iter;
	bool removed = false;
	for (iter = mWatchees.begin(); iter != mWatchees.end(); iter ++) {
		if ((*iter)->fd == pWatchee->fd) {
			cdbg << "Removed Watchee [" << pWatchee->FileName << "]" << endl;
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
void FileEventWatcher::stopWatchingForFileEvents() {
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
	
	cdbg << "FileEventWatcher :: Watching [" << (int) mPollFDs.size() << " Files] for Events..." << endl;
	mPolling = true;
	while (mPolling) {
		// poll the open files
		poll(&mPollFDs[0], mPollFDs.size(), -1);
				
		// file events have happened, check for them and dispatch
		apply_func(mPollFDs, &FileEventWatcher::handleEventsOnFile, this);
	}
}
