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

#ifndef __FileEventWatcher_h
#define __FileEventWatcher_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <sys/poll.h>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
/**
 * \enum  FileWatchType
 * \brief Specifies the type of file watching to be done
 *
 * WATCH_IN    dictates that the file should only be watched for reads
 * WATCH_OUT   dictates that the file should only be watched for writes
 * WATCH_INOUT dictates that the file should be watched for reads and writes
 */
typedef enum {
	WATCH_IN,
	WATCH_OUT,
	WATCH_INOUT
} FileWatchType;

/**
 * \class FileWatchee
 * \brief Structure to hold information about file watchees
 */
class FileWatchee {
public:
	// public member variables
	std::string		FileName;			///< Name of the file to watch
	FileWatchType		WatchType;			///< Method to watch the file with
	int			fd;				///< File Descriptor of the opened file
	
	// construction / deconstruction
	FileWatchee();						///< Default Constructor
	FileWatchee(std::string fileName, FileWatchType watchType, int fileDescriptor); ///< Init Constructor
	virtual ~FileWatchee();					///< Destructor
};

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class FileEventWatcher
 * \brief Class to efficiently watch for changes in files
 *
 * This class uses the poll() mechanism to efficiently watch for file changes
 * rather than using select() which does not scale well.
 *
 * FileEventWatcher is essentially a wrapper for poll() which makes it easy
 * to integrate into any program
 */
class FileEventWatcher {
public:
	// public functions
	void			addFileToWatch(std::string FileName, FileWatchType WatchType); ///< Add a file to watch for events 
	void 			watchForFileEvents();		///< Watch for events on already specified files
	
	// construction / deconstruction
	FileEventWatcher();					///< Default Constructor
	virtual ~FileEventWatcher();				///< Destructor

protected:
	// private functions
	
	// private member variables
	std::list< boost::shared_ptr<FileWatchee> > mWatcheeList; ///< List of files being watched
	std::vector<struct pollfd> mPollFDs;			///< Array of pollfd for the call to poll()
};

//////////////////////////////////////////////////////////////////////////////

}

#endif // __FileEventWatcher_h
