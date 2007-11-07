    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  UtilFile.hpp
*** \brief UtilFile class header file
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

#ifndef __UtilFile_h
#define __UtilFile_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "UtilFile.hpp"
#include <cstdlib>
#include <string>

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
 * \class UtilFile
 * \brief Main UtilFile class
 *
 * This is an interface for classes wishing to receive socket events
**/
class UtilFile {
public:
	// Public Member Functions
	static bool 			createDirectory(std::string const & FileName); /// create a directory
	static void 			relativeToAbsolute(std::string & FilePath); /// Relative to absolute path
	static bool 			touch(std::string const & FilePath); ///< Touch a file / directory
	static bool 			touchRecursive(std::string const & FilePath, bool DoRecursive = true); ///< Recursively touch a file / directory
	
	// Construction / Deconstruction
	UtilFile();						///< Default Constructor
	virtual ~UtilFile();					///< Destructor

private:
	// Private Member Functions

	// Private Member Variables
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __UtilFile_h
