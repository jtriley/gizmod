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
#include "../libH/UtilTime.hpp"
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
using namespace Gizmod;

////////////////////////////////////////////////////////////////////////////
// Typedef's / defines
///////////////////////////////////////

/**
 * \def    PROC_PATH
 * \brief  Path to /proc
 */
#define PROC_PATH		"/proc"

/**
 * \def    DEFAULT_UPDATE_DELAY
 * \brief  The default amount of time between process tree rebuilds
 */
#define DEFAULT_UPDATE_DELAY	2500000

////////////////////////////////////////////////////////////////////////////
// Statics 
///////////////////////////////////////
	
mutex Processes::mMutexUpdate;					  ///< Update mutex, to make thread safe
map< string, shared_ptr<Process> > Processes::mProcesses;	  ///< Process map shared between all instances
unsigned long Processes::mLastUpdateTime = 0;  			  ///< Time of last tree update
unsigned long Processes::mMsBetweenUpdates = DEFAULT_UPDATE_DELAY; ///< Time between updates

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Processes Default Constructor
 */
Processes::Processes() {
	// update the process tree if necessary
	isProcessRunning("");
}

/**
 * \brief Process Default Constructor
 */
Process::Process() {
	PID = -1;
}

/**
 * \brief Processes Destructor
 */
Processes::~Processes() {
}

/**
 * \brief Process Destructor
 */
Process::~Process() {
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
	if (UtilTime::getTicks() - mLastUpdateTime >= mMsBetweenUpdates)
		updateProcessTree();
	
	// lock the processes
	mutex::scoped_lock lock(mMutexUpdate);
	
	shared_ptr<Process> pProcess = mProcesses[ProcessName];
	if ( (!pProcess) || (pProcess->State == "Z") )
		return -1;
	else
		return pProcess->PID;
}

/**
 * \brief  Set the time between updates in seconds
 * \param  Seconds Number of seconds between updates
 */
void Processes::setTimeBetweenUpdates(float Seconds) {
	mMsBetweenUpdates = (unsigned long) (Seconds * 1000000.0f);
}

/**
 * \brief  Force an update of the process tree
 */
void Processes::updateProcessTree() {
	cdbg5 << "Building Process Tree" << endl;
	if (!filesystem::exists(path(PROC_PATH))) {
		cdbg << "Error Building Process Tree!" << endl;
		return;
	}
	
	// lock the processes
	mutex::scoped_lock lock(mMutexUpdate);
	
	// clear out the process list
	mProcesses.clear();
		
	// create some data structures for parsing the info
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	char_separator<char> Separators(" ");
	
	// now register the event nodes
	// get a file listing
	directory_iterator endItr;
	for (directory_iterator iter(PROC_PATH); iter != endItr; iter ++) {
		string StatPath = iter->string() + "/stat";
		try {
			if ( (filesystem::is_directory(*iter)) && (filesystem::exists(path(StatPath))) ) {
				ifstream StatFile(StatPath.c_str());
				if (!StatFile.is_open())
					continue;
				string Line;
				getline(StatFile, Line);
				tokenizer tok(Line, Separators);
				shared_ptr<Process> pProcess = shared_ptr<Process>(new Process);
				int count = 0;
				for(tokenizer::iterator iter = tok.begin(); iter!= tok.end(); iter ++, count ++) {
					bool BreakFor = false;
					switch (count) {
					case 0:
						try {
							pProcess->PID = lexical_cast<int>(*iter);
						} catch (bad_lexical_cast const & e) {
							// unable to convert
							BreakFor = true;
						}
						break;
					case 1:
						pProcess->Name = iter->substr(1, iter->length() - 2);
						break;
					case 2:
						pProcess->State = *iter;
						mProcesses.insert(make_pair(pProcess->Name, pProcess));
						BreakFor = true;
						break;
					}
					
					if (BreakFor)
						break;
				}
			}
		} catch (filesystem_error const & e) {
			// no worries, just continue
		}
	}
	
	// update the time
	mLastUpdateTime = UtilTime::getTicks();	
}
