    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  FileEventWatcher.hpp
*** \brief FileEventWatcher class header file
***
*****************************************
  *****************************************
    **/

/*

Copyright (c) 2006, Tim Burrell
All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "FileEventWatcher.hpp"
#include "Debug.hpp"
#include "Exception.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief FileEventWatcher Default Constructor
 */
FileEventWatcher::FileEventWatcher() {
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
void FileEventWatcher::addFileToWatch(string FileName, FileWatchType WatchType) {
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
	poll(&mPollFDs[0], mPollFDs.size(), -1);
}
