    /** 
  *********************************************************************
*************************************************************************
*** 
*** \file  Debug.cpp
*** \brief Debug class blody
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

#include "Debug.hpp"

using namespace H;

////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////

bool 	Debug::mDebug = false;
int	Debug::mVerbosity = 0;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
Debug::Debug(int ThisVerbosity) {
	mThisVerbosity = ThisVerbosity;
}

/**
 * \brief Destructor
 */
Debug::~Debug() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////
