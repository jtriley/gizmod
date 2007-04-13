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
#include <map>
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
 * \enum  FileDeviceType
 * \brief Specifies the type of device watching interface (poll / inotify)
 *
 * WATCH_POLL     dictates that the file is a poll device
 * WATCH_INOTIFY  dictates that the file is an inotify device
 */
typedef enum {
	WATCH_POLL,
	WATCH_INOTIFY
} FileDeviceType;

//////////////////////////////////////////////////////////////////////////////
// DeviceInfo Class Definition
///////////////////////////////////////

/**
 * \class DeviceInfo
 * \brief Structure to hold information about devices
 */
class DeviceInfo {
public:
	// public member variables
	int				DeviceIDBusType;	///< Bus Type of the device
	int				DeviceIDProduct;	///< Product code of the device
	int				DeviceIDVendor;		///< Vendor ID of the device
	int				DeviceIDVersion;	///< Version of the device
	std::string			DeviceName;		///< Name of the device
	std::string			FileName;		///< Name of the file to watch
		
	// construction / deconstruction
	DeviceInfo();						///< Default Constructor
	DeviceInfo(const DeviceInfo & DeviceInformation); 	///< Init Constructor
	DeviceInfo(std::string DeviceName, std::string FileName, int DeviceIDBusType, int DeviceIDVendor, int DeviceIDProduct, int DeviceIDVersion); ///< Init Constructor
	virtual ~DeviceInfo();					///< Destructor
};

//////////////////////////////////////////////////////////////////////////////
// FileWatchee Class Definition
///////////////////////////////////////

/**
 * \class FileWatchee
 * \brief Structure to hold information about file watchees
 */
class FileWatchee : public DeviceInfo {
public:
	// public member variables
	FileDeviceType			DeviceType;		///< Type of the device
	short				Events;			///< Raw event flag bitmask
	int				fd;			///< File Descriptor of the opened file (poll)
	FileWatchType			WatchType;		///< Method to watch the file with
	int				wd;			///< Watch descriptor of the device (inotify)
		
	// construction / deconstruction
	FileWatchee();						///< Default Constructor
	FileWatchee(std::string fileName, FileWatchType watchType, short events, int fileDescriptor, int watchDescriptor, std::string deviceName, int deviceIDBusType, int deviceIDVendor, int deviceIDProduct, int deviceIDVersion); ///< Init Constructor
	virtual ~FileWatchee();					///< Destructor
};

//////////////////////////////////////////////////////////////////////////////
// FileEventWatcher Class Definition
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
 * 
 * Also use the linux kernel's inotify event to get information about directory changes
 * (add / remove files, etc).  Unfortunately inotify doesn't work with event node updates
 * so poll is still required
 */
class FileEventWatcher {
public:
	// public functions
	boost::shared_ptr<FileWatchee> 	addFileToWatch(std::string FileName, FileWatchType WatchType); ///< Add a file to watch for events 
	boost::shared_ptr<FileWatchee>	getWatcheeByFileDescriptor(int fd); ///< Get a Watchee by file descriptor
	boost::shared_ptr<FileWatchee>	getWatcheeByPath(std::string Path); ///< Get a Watchee by file name
	boost::shared_ptr<FileWatchee>	getWatcheeByWatchDescriptor(int wd); ///< Get a Watchee by watch descriptor
	virtual void			onFileEventCreate(boost::shared_ptr<FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a new file is created
	virtual void			onFileEventDelete(boost::shared_ptr<FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a file is deleted
	virtual void			onFileEventDisconnect(boost::shared_ptr<FileWatchee> pWatchee); ///< Event triggered when a device is disconnected
	virtual void			onFileEventRead(boost::shared_ptr<FileWatchee> pWatchee, boost::shared_ptr< DynamicBuffer<char> > pReadBuffer); ///< Event triggered when data is waiting on a device
	virtual void			onFileEventRegister(boost::shared_ptr<FileWatchee> pWatchee); ///< Event triggered when a new device is registered
	void 				removeWatchee(boost::shared_ptr<FileWatchee> pWatchee); ///< Remove a Watchee from the list
	void				stopWatchingForFileEvents();	///< Disable event watching
	void 				watchForFileEvents();		///< Watch for events on already specified files
	
	// construction / deconstruction
	FileEventWatcher();						///< Default Constructor
	virtual ~FileEventWatcher();					///< Destructor

private:
	// private functions
	void 				buildPollFDArrayFromWatchees();	///< (Re)build mPollFDs array for the call to poll()
	void 				buildPollFDArrayFunctor(std::pair< int, boost::shared_ptr<FileWatchee> > WatcheePair); ///< Functor for building mPollFDs
	FileWatchType 			getType(int Index);		///< Get the type of file event that happened on specified file
	void 				handleEventsOnFile(struct pollfd & item); ///< Functor that handles file events after a poll()
	boost::shared_ptr< H::DynamicBuffer<char> > readFromFile(int fd); ///< Read from file and return the contents in a vector
	void 				removeAllWatchDescriptors();	///< Remove all watch descriptors
	void 				removeWatchDescriptor(int wd);	///< Remove a watch descriptor
	
	// private member variables
	int				mInotifyFD;			///< Inotify File Descriptor
	std::vector<int>	 	mInotifyWDs;			///< Array of watch descriptors for inotify
	std::vector<struct pollfd> 	mPollFDs;			///< Array of pollfd for the call to poll()
	bool				mPolling;			///< Continue polling?
	std::map< int, boost::shared_ptr<FileWatchee> > mWatchees; 	///< Map of files being watched
};

//////////////////////////////////////////////////////////////////////////////
// Exception Classes
///////////////////////////////////////

/// Exception that indicates a device has disconnected
class DeviceDisconnectException : public std::exception {
};

/// Exception that indicates a watchee was not found while iterating
class WatcheeNotFoundException : public std::exception {
};

//////////////////////////////////////////////////////////////////////////////

}

#endif // __FileEventWatcher_h
