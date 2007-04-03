    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoDaemon.hpp
*** \brief GizmoDaemon class header file
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

#ifndef __GizmoDaemon_h
#define __GizmoDaemon_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmodEventHandlerInterface.hpp"
#include <string>
#include <boost/python.hpp>

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoDaemon
 * \brief Main GizmoDaemon class
 */
class GizmoDaemon {
public:
	// public functions
	void				enterLoop();		///< Enter the main run loop
	std::string			getVersion();		///< Get version string
	void				initGizmod();		///< Initialize GizmoDaemon Evolution
	bool				initialize(int argc, char ** argv); ///< generic init stuff, command line, etc
		
	// construction / deconstruction
	GizmoDaemon();						///< Default Constructor
	virtual ~GizmoDaemon();					///< Destructor

private:
	// private functions
	std::string	 		getProps();		///< Get version information
	void				initPython();		///< Initialize Python
	
	// private member vars
	std::string			mConfigDir;		///< Configuration scripts directory
	std::string			mEventsDir;		///< Event node directory
	GizmodEventHandlerInterface * 	mpPyDispatcher;		///< The GizmoDaemonDispatcher Python object
};

#endif // __GizmoDaemon_h
