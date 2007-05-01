    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Processes.cpp
*** \brief Processes class body
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

#include "Processes.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <fstream>
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's / defines
///////////////////////////////////////

/**
 * \def    PROC_PATH
 * \brief  Path to /proc
 */
#define PROC_PATH	"/proc"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Processes Default Constructor
 */
Processes::Processes() {
}

/**
 * \brief Processes Destructor
 */
Processes::~Processes() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Check is a process is running
 * \param  ProcessName The name of the process to check on
 * \return PID of the process if found, or a negative value if not found
 */
int Processes::isProcessRunning(std::string ProcessName) {
	if (!filesystem::exists(path(PROC_PATH)))
		return -1;
		
	// now register the event nodes
	// get a file listing
	int pid = -1;
	directory_iterator endItr;
	for (directory_iterator iter(PROC_PATH); iter != endItr; iter ++) {
		string StatPath = iter->string() + "/stat";
		try {
			if ( (filesystem::is_directory(*iter)) && (filesystem::exists(path(StatPath))) ) {
				std::ifstream StatFile(StatPath.c_str());
				if (!StatFile.is_open())
					continue;
				string Line;
				getline(StatFile, Line);
				tokenizer<> tok(Line);
				int count = 0;
				for(tokenizer<>::iterator iter = tok.begin(); iter!= tok.end(); iter ++, count ++) {
					switch (count) {
					case 0:
						try {
							pid = lexical_cast<int>(*iter);
						} catch (bad_lexical_cast const & e) {
							// unable to convert
							continue;
						}
						break;
					case 1:
						if (ProcessName ==  *iter)
							return pid;
						break;
					}
				}
			}
		} catch (filesystem_error const & e) {
			// no worries, just continue
		}
	}
	
	return -1;
}
