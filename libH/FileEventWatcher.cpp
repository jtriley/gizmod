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
#include <boost/bind.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def   READ_BUF_SIZE 
 * \brief Default size of the read buffer for the automatic file reader
 */
#define READ_BUF_SIZE	65536

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
FileWatchee::FileWatchee(std::string fileName, FileWatchType watchType, int fileDescriptor) {
	FileName = fileName;
	WatchType = watchType;
	fd = fileDescriptor;
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
	
	int fd = open(FileName.c_str(), flags);
	if (fd == -1)
		throw H::Exception("Failed to Open file [" + FileName + "] with Mode [" + ModeString + "]", __FILE__, __FUNCTION__, __LINE__);
	
	// Add the new watchee to the list
	struct pollfd PollFD;
	PollFD.fd = fd;
	PollFD.events = events;
	PollFD.revents = 0;
	mPollFDs.push_back(PollFD);
	shared_ptr<FileWatchee> pWatchee(new FileWatchee(FileName, WatchType, fd));
	mWatcheeList.push_back(pWatchee);
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
 * \brief  Read the input event waiting on a file descriptor
 * \param  fd The file descriptor
 * \return The results of the read (DynamicBuffer)
 */
shared_ptr< DynamicBuffer<char> > FileEventWatcher::readFromFile(int fd) {
	shared_ptr< DynamicBuffer<char> > pBuffer(new DynamicBuffer<char>);
	
	char ReadBuffer[READ_BUF_SIZE];
	ssize_t BytesRead;
	do {
		BytesRead = read(fd, ReadBuffer, READ_BUF_SIZE);
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
		shared_ptr< DynamicBuffer<char> > pBuffer = readFromFile(item.fd);
	}
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
		for_each(mPollFDs.begin(), mPollFDs.end(), bind(&FileEventWatcher::handleEventsOnFile, this, _1));
	}
}
