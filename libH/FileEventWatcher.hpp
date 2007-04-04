    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  FileEventWatcher.hpp
*** \brief FileEventWatcher header
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
#include "DynamicBuffer.hpp"

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
	WATCH_INVALID = -1,
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

private:
	// private functions
	FileWatchType 		getType(int Index);		///< Get the type of file event that happened on specified file
	void 			handleEventsOnFile(struct pollfd & item); ///< Functor that handles file events after a poll()
	boost::shared_ptr< H::DynamicBuffer<char> > readFromFile(int fd); ///< Read from file and return the contents in a vector
	
	// private member variables
	std::vector<struct pollfd> mPollFDs;			///< Array of pollfd for the call to poll()
	bool			mPolling;			///< Continue polling?
	std::list< boost::shared_ptr<FileWatchee> > mWatcheeList; ///< List of files being watched
};

//////////////////////////////////////////////////////////////////////////////

}

#endif // __FileEventWatcher_h
