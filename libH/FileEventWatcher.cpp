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
}

/**
 * \brief FileEventWatcher Destructor
 */
FileEventWatcher::~FileEventWatcher() {
}

/**
 * \brief FileWatchee Default Constructor
 */
FileWatchee::FileWatchee() {
	WatchType = WATCH_IN;
	fd = -1;
}

/**
 * \brief FileWatchee Init Constructor
 */
FileWatchee::FileWatchee(std::string fileName, FileWatchType watchType, int fileDescriptor, std::string deviceName) {
	FileName = fileName;
	WatchType = watchType;
	fd = fileDescriptor;
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
void FileEventWatcher::addFileToWatch(std::string FileName, FileWatchType WatchType) {
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
	
	// open the device
	int fd = open(FileName.c_str(), flags);
	if (fd == -1)
		throw H::Exception("Failed to Open file [" + FileName + "] with Mode [" + ModeString + "]", __FILE__, __FUNCTION__, __LINE__);
	
	// get the device name
	char DeviceName[DEVICE_NAME_BUF_SIZE] = {'\0'};
	if (ioctl(fd, EVIOCGNAME(sizeof(DeviceName)), DeviceName) < 0)
		throw H::Exception("Failed to Get Device Name for [" + FileName + "]", __FILE__, __FUNCTION__, __LINE__);
	cdbg << "Found Device [" << FileName << "]: " << DeviceName << endl;
	
	// Add the new watchee to the list
	struct pollfd PollFD;
	PollFD.fd = fd;
	PollFD.events = events;
	PollFD.revents = 0;
	mPollFDs.push_back(PollFD);
	shared_ptr<FileWatchee> pWatchee(new FileWatchee(FileName, WatchType, fd, DeviceName));
	onFileWatcheeAdded(pWatchee);
	mWatchees.push_back(pWatchee);
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
 * \return Type of the event (shared_ptr to FileWatchee)
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
 * \brief  Event triggered when a new FileWatchee is added
 * \param  Device The new file (device) being watched
 */
void FileEventWatcher::onFileWatcheeAdded(boost::shared_ptr<FileWatchee> Device) {
	// overload me
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
 * \brief Functor that checks for and handles events on a pollfd object
 * \param item The item to check and handle events for
 */
void FileEventWatcher::handleEventsOnFile(struct pollfd & item) {
	if (item.revents & POLLIN) {
		try {
			shared_ptr< DynamicBuffer<char> > pBuffer = readFromFile(item.fd);
		} catch (H::DeviceDisconnectException & e) {
			shared_ptr<FileWatchee> pWatchee = getWatcheeByFileDescriptor(item.fd);
			if (pWatchee) {
				cout << "Disconnect from Device [" << pWatchee->DeviceName <<"] at [" << pWatchee->FileName << "]" << endl;
			} else {
				// not found, not a big deal
				cout << "Disconnect from Device [Unknown]" << endl;
			}
		}
	}
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
		
		cdbg << "Event Detected" << endl;
		
		// file events have happened, check for them and dispatch
		apply_func(mPollFDs, &FileEventWatcher::handleEventsOnFile, this);
	}
}
