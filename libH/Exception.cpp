    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Exception.hpp
*** \brief Exception class header file
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

#include "Exception.hpp"
#include "Debug.hpp"
#include "stringconverter.hpp"
#include <sstream>

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Exception Default Constructor
 */
Exception::Exception(const std::string & Message, ExceptionType Type) {
	mMessage = Message;
	mType = Type;
}

/**
 * \brief Exception Advanced Constructor
 */
Exception::Exception(const std::string & Message, const string & File, const string & Function, int LineNumber, ExceptionType Type) {
	if (Debug::getDebugEnabled())
		mMessage = "Exception in [" + File + "] :: [" + Function + "] @ [Line " + stringconverter(LineNumber) + "] -- " + Message;
	else
		mMessage = Message;
	mType = Type;
}

/**
 * \brief Exception Destructor
 */
Exception::~Exception() throw() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

