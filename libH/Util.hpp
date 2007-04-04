    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Util.hpp
*** \brief Util class header file
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

#ifndef __Util_h
#define __Util_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#include <boost/any.hpp>
#include <boost/function.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Global Functions
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Util
 * \brief Main Util class
 *
 * This class provides static time routines for sleeping and finding the current time
 *
 * It also can be instantiated to provide a time duration watcher
 */
class Util {
public:
	// Public Member Functions
	
	// Construction / Deconstruction
	Util();
	virtual ~Util();

private:
	// Private Member Functions

	// Private Member Variables
};

} // H namespace

#endif // __Util_h
