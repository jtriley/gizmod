    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketException.hpp
*** \brief SocketException class header file
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

#ifndef __SocketException_h
#define __SocketException_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Exception.hpp"

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
 * \class SocketException
 * \brief Main SocketException class
 *
 * This class provides an easy way for dealing with signals
 */
class SocketException : public Exception {
public:
	// Public Member Functions
	
	// Construction / Deconstruction
	SocketException(std::string const & Message, ExceptionType Type = EXCEPTION_NORMAL); ///< Default Constructor
	SocketException(std::string const & Message, std::string const & File, std::string const & Function, int LineNumber, ExceptionType Type = EXCEPTION_NORMAL); ///< Init Constructor
	virtual ~SocketException() throw() ;					///< Destructor

private:
	// Private Member Functions

	// Private Member Variables
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __SocketException_h
