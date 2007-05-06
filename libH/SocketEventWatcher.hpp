    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketEventWatcher.hpp
*** \brief SocketEventWatcher class header file
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

#ifndef __SocketEventWatcher_h
#define __SocketEventWatcher_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "SocketInterface.hpp"
#include "DynamicBuffer.hpp"
#include <cstdlib>

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
 * \class SocketEventWatcher
 * \brief Main SocketEventWatcher class
 *
 * This is an interface for classes wishing to receive socket events
 */
class SocketEventWatcher {
public:
	// Public Member Functions
	virtual void 				onSocketRead(SocketInterface const & iSocket, DynamicBuffer<char> & ReadBuffer) = 0; ///< Handle a socket read
	virtual void 				onSocketDisconnect(SocketInterface const & iSocket) = 0; ///< Handle a socket read
	
	// Construction / Deconstruction
	SocketEventWatcher();						///< Default Constructor
	virtual ~SocketEventWatcher();					///< Destructor

private:
	// Private Member Functions

	// Private Member Variables
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __SocketEventWatcher_h
