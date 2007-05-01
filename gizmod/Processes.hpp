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
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Processes
 * \brief Base class for functions related to operating system processes
 */
class Processes {
public:
	// public functions

	// construction / deconstruction
	Processes();							///< Default Constructor
	virtual ~Processes();						///< Destructor
	
	// public static functions
	int			isProcessRunning(std::string ProcessName); ///< Check is a process is running

protected:
	// private functions
	
	// private member variables
};

#endif // __Processes_h
