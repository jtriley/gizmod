    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  UtilFile.cpp
*** \brief UtilFile class body
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

#include "UtilFile.hpp"
#include "Debug.hpp"
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#ifndef WIN32
	#include <dirent.h>
	#include <unistd.h>
#else
	#include <Windows.h>
	#include <shlobj.h>
#endif
#include <fcntl.h>
#include <time.h>

using namespace H;
using namespace std;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

/**
 * \def   DIRCHAR
 * \brief Platform dependant directory separator char
**/

/**
 * \def   DIRSTR
 * \brief Platform dependant directory separator string
**/

#ifdef WIN32
	#define DIRCHAR		'\\'
	#define DIRSTR		"\\"
#else
	#define DIRCHAR		'/'
	#define DIRSTR		"/"
#endif

////////////////////////////////////////////////////////////////////////////
// Construction / Deconstruction
///////////////////////////////////////

/**
 * \brief Default Constructor
**/
UtilFile::UtilFile() {
}

/**
 * \brief Destructor
**/
UtilFile::~UtilFile() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Create a directory
 * \param  FileName The directory to create
 * \return true on success
**/
bool UtilFile::createDirectory(std::string const & FileName) {
#ifndef WIN32
	if (mkdir(FileName.c_str(), 0755) == -1)
		return false;
	else
		return true;
#else
	return CreateDirectory(FileName, NULL) != 0;
#endif
}

/**
 * \brief  Change a file path from relative to absolute
 * \param  FilePath The path
**/
void UtilFile::relativeToAbsolute(std::string & FilePath) {
	size_t tPos;
	if ((tPos = FilePath.find("~" DIRSTR)) == string::npos)
		return;		
	const char * home = getenv("HOME");
	if (!home)
		return;
	FilePath = FilePath.substr(0, tPos) + home + DIRSTR + FilePath.substr(2);
}

/**
 * \brief  Touch a file
 * \param  FilePath The file / directory to touch
 * \return true on success
**/
bool UtilFile::touch(std::string const & FilePath) {
	// check if it's a directory
	if (FilePath[FilePath.length() - 1] == DIRCHAR) {
		// create a dir
		return createDirectory(FilePath);
	} else {
		// create a file
		ofstream oFile(FilePath.c_str(), ios::app);
		if (!oFile.is_open())
			return false;
		return true;
	}
}

/**
 * \brief  Recursively touch a file
 * \param  FilePath The file to touch
 * \param  DoRecursive Do the operation recursively if true
 * \return true on success
**/
bool UtilFile::touchRecursive(std::string const & FilePath, bool DoRecursive) {	
	// let's try to create it!
	if (touch(FilePath))
		return true;		
	// recursion requested?
	if (!DoRecursive)
		return false;
	
	// if still no go break it down into smaller pieces
	string strFilePath = FilePath;
	int Modifier = 0;
	if (strFilePath[strFilePath.length() - 1] == DIRCHAR)
		Modifier = 1;
	size_t sPos = strFilePath.rfind(DIRSTR, strFilePath.length() - Modifier - 1);
	if (sPos == string::npos)
		return touch(FilePath);
			
	string SubLevel = strFilePath.substr(0, sPos + 1);
	if (!touchRecursive(SubLevel, true))
		return false;
		
	return touch(FilePath);
}
