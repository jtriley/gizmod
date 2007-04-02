    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Exception.cpp
*** \brief Exception class body
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

#ifndef __Exception_h
#define __Exception_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

/**
 * \typedef ExceptionType
 *
 * Enum for the different Exception types
 */
typedef enum {
	EXCEPTION_INFO,
	EXCEPTION_WARNING,
	EXCEPTION_NORMAL,
	EXCEPTION_FATAL
} ExceptionType;

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Exception
 * \brief Generic Exception class
 *
 * Generic Exception class which takes a string message as a constructor
 * For throwing informative error messages
 */
class Exception : public std::exception {
public:
	/// Get the type of exception
	virtual const ExceptionType getExceptionType() { return mType; };
	
	/// Get the exception's message
	virtual const std::string & getExceptionMessage() { return mMessage; };
	
	/// Get the exceptions message
	virtual const char * what() { return mMessage.c_str(); };
	
	/// Get the exceptions message
	virtual const char * message() { return mMessage.c_str(); };
	
	/// operator overload for const char * -- get the Exception's message
	virtual operator const char* () const { return mMessage.c_str(); };
	
	/// Default Constructor
	Exception(const std::string & Message, ExceptionType Type = EXCEPTION_NORMAL);
	
	/// Extended Constructor
	Exception(const std::string & Message, const std::string & File, const std::string & Function, int LineNumber, ExceptionType Type = EXCEPTION_NORMAL);
	
	/// Destructor
	virtual ~Exception() throw() ;

protected:
	std::string	mMessage; 	///< the Exception's informational message
	ExceptionType	mType;		///< the type of the exceptionl 
};

//////////////////////////////////////////////////////////////////////////////

}

#endif // __Exception_h
