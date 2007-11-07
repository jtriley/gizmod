    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SignalHandler.hpp
*** \brief SignalHandler class header file
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

#ifndef __SignalHandler_h
#define __SignalHandler_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Debug.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/any.hpp>
#include <boost/function.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedef's / Defines
///////////////////////////////////////
		
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class SignalHandler
 * \brief Main SignalHandler class
 *
 * This class provides an easy way for dealing with signals
**/
class SignalHandler {
public:
	// Public Member Functions
	void			initSignals();			///< Initialize the signal handler
	virtual void		onSignalSegv();			///< Signal handler for SEGV
	virtual void		onSignalInt();			///< Signal handler for INT
	virtual void		onSignalHup();			///< Signal handler for HUP
	virtual void		onSignalQuit();			///< Signal handler for QUIT
	virtual void		onSignalKill();			///< Signal handler for KILL
	virtual void		onSignalTerm();			///< Signal handler for TERM
	virtual void		onSignalStop();			///< Signal handler for STOP
	virtual void		onSignalUnknown(int Signal);	///< Signal handler for Unknown Signals
	
	// Construction / Deconstruction
	SignalHandler();
	virtual ~SignalHandler();

	// public member variables
	static SignalHandler * 	mpThis;				///< Pointer to this

private:
	// Private Member Functions
	static void 		signalHandler(int Signal);	///< Signal handler

	// Private Member Variables
};

} // H namespace

#endif // __SignalHandler_h
