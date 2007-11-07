    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Processes.hpp
*** \brief Processes class header
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

#ifndef __Processes_h
#define __Processes_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Process Class Definition
///////////////////////////////////////

/**
 * \class Process
 * \brief Class that holds info about each process
**/
class Process {
public:
	// public member variables
	std::string			Name;				///< Name of the process
	unsigned int			PID;				///< Process ID
	std::string			State;				///< State of the process
	
	// public functions

	// construction / deconstruction
	Process();							///< Default Constructor
	virtual ~Process();						///< Destructor
	
private:
	// private functions
	
	// private member variables
};
	
//////////////////////////////////////////////////////////////////////////////
// Processes Class Definition
///////////////////////////////////////

/**
 * \class Processes
 * \brief Base class for functions related to operating system processes
**/
class Processes {
public:
	// public functions

	// construction / deconstruction
	Processes();							///< Default Constructor
	virtual ~Processes();						///< Destructor
	
	// public static functions
	static int		isProcessRunning(std::string ProcessName); ///< Check is a process is running
	static void		setTimeBetweenUpdates(float Seconds);	///< Time between updates in seconds
	static void		updateProcessTree();			///< Force an update of the process tree

private:
	// private functions
	
	// private member variables
	static unsigned long	mLastUpdateTime;			///< Time of last tree update
	static unsigned long	mMsBetweenUpdates;			///< Time between updates
	static boost::mutex	mMutexUpdate;				///< Update mutex, to make thread safe
	static std::map< std::string, boost::shared_ptr<Process> > mProcesses;	///< Process map shared between all instances
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __Processes_h
