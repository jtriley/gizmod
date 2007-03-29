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

Copyright (c) 2006, Tim Burrell
All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

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
