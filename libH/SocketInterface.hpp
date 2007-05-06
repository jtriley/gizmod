    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketInterface.hpp
*** \brief SocketInterface class header file
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

#ifndef __SocketInterface_h
#define __SocketInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "SocketInterface.hpp"
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
 * \class SocketInterface
 * \brief Main SocketInterface class
 *
 * This is an interface for classes wishing to receive socket events
 */
class SocketInterface {
public:
	// Public Member Functions
	virtual int			getSocket() const = 0;		///< Get the socket
	
	// Construction / Deconstruction
	SocketInterface();						///< Default Constructor
	virtual ~SocketInterface();					///< Destructor

private:
	// Private Member Functions

	// Private Member Variables
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __SocketInterface_h
