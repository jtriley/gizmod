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
Exception::Exception(const std::string & Message, const std::string & File, const std::string & Function, int LineNumber, ExceptionType Type) {
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

