    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketException.cpp
*** \brief SocketException class body
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

#include "SocketException.hpp"
#include "Debug.hpp"
#include "Exception.hpp"

using namespace H;
using namespace std;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction / Deconstruction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
SocketException::SocketException(std::string const & Message, ExceptionType Type) : Exception(Message, Type) {
}

/**
 * \brief Init Constructor
 */
SocketException::SocketException(std::string const & Message, std::string const & File, std::string const & Function, int LineNumber, ExceptionType Type) : Exception(Message, File, Function, LineNumber, Type) {
}


/**
 * \brief Destructor
 */
SocketException::~SocketException() throw() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

