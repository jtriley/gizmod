    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  CPUUsage.cpp
*** \brief CPUUsage class body
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

#include "CPUUsage.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/UtilTime.hpp"
#include <fstream>
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's / defines
///////////////////////////////////////

/**
 * \def    PROC_STAT_PATH
 * \brief  Path to /proc/stat
 */
#define PROC_STAT_PATH		"/proc/stat"

/**
 * \def    DEFAULT_UPDATE_DELAY
 * \brief  The default amount of seconds between process tree rebuilds
 */
#define DEFAULT_UPDATE_DELAY	0.25f

////////////////////////////////////////////////////////////////////////////
// Statics 
///////////////////////////////////////
	
////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief CPUUsage Default Constructor
 */
CPUUsage::CPUUsage() : mThreadProc(this) {
	mSecsBetweenUpdates = DEFAULT_UPDATE_DELAY;
	mWatching = false;
	getNumCPUs();
}

/**
 * \brief CPUUsage Destructor
 */
CPUUsage::~CPUUsage() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the number of CPUs on the system
 * \return The number of CPUs
 */
size_t CPUUsage::getNumCPUs() {
	if (mCPUUsage.size() == 0) {
		if (!filesystem::exists(path(PROC_STAT_PATH))) {
			cdbg << "Can not update CPU Usage Stats!" << endl;
			return -1;
		}
					
		// open the file
		ifstream StatFile(PROC_STAT_PATH);
		if (!StatFile.is_open()) {
			cdbg << "Error Updating CPU Usage Stats!" << endl;
			return -1;
		}
		
		// create some datastructures for parsing the line
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		char_separator<char> Separators(" ");	
		
		// read the contents
		string Line;
		int cpus = 0;
		while (true) {
			// get the line and make sure it's related to cpu information
			getline(StatFile, Line);
			if (Line.find("cpu") != 0)
				break;
			cpus ++;
		}
		mCPUUsage.resize(cpus);
		mCPUUsageAvg.resize(cpus);
	}
	
	return mCPUUsage.size() - 1;
}

/**
 * \brief  Start the Usage watcher thread
 */
void CPUUsage::init() {
	// initialize the event handler thread
	thread thrd(mThreadProc);
}

/**
 * \brief  Set the time between updates in seconds
 * \param  Seconds Number of seconds between updates
 */
void CPUUsage::setTimeBetweenUpdates(float Seconds) {
	mSecsBetweenUpdates = Seconds;
}

/**
 * \brief  Shutdown the CPUUsage watcher
 */
void CPUUsage::shutdown() {
	mWatching = false;
	while (mThreading)
		UtilTime::sleep(0.1f);
}

/**
 * \brief  The thread procedure loop
 */
void CPUUsage::threadProc() {
	// wait for events to occur
	mWatching = true;
	while (mWatching) {
		updateUsageStats();
		UtilTime::sleep(mSecsBetweenUpdates);
	}
}

/**
 * \brief  Force an update of the CPU Usage stats
 */
void CPUUsage::updateUsageStats() {
	if (!filesystem::exists(path(PROC_STAT_PATH))) {
		cdbg << "Can not update CPU Usage Stats!" << endl;
		return;
	}
				
	// open the file
	ifstream StatFile(PROC_STAT_PATH);
	if (!StatFile.is_open()) {
		cdbg << "Error Updating CPU Usage Stats!" << endl;
		return;
	}
	
	// create some datastructures for parsing the line
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	char_separator<char> Separators(" ");	
	
	// read the contents
	string Line;
	size_t CurCPU = 0;
	do {
		// get the line and make sure it's related to cpu information
		getline(StatFile, Line);
		if (Line.find("cpu") != 0)
			break;
		
		// process the line
		tokenizer tok(Line, Separators);
		int count = 0;
		int Fields[CPUUSAGE_MAX];
		memset(Fields, 0, sizeof(int) * CPUUSAGE_MAX);
		for(tokenizer::iterator iter = tok.begin(); iter!= tok.end(); iter ++, count ++) {
			if (count == 0)
				continue;
			try {
				Fields[count] = lexical_cast<int>(*iter);
			} catch (bad_lexical_cast const & e) {
				// no worries, continue
				cdbg << "Error parsing CPUUsage for CPU [" << CurCPU << "]" << endl;
				continue;
			}
		}
		
		// compute the total
		double Total = 0.0;
		for (int lp = 0; lp < CPUUSAGE_RESERVED; lp ++)
			Total += Fields[lp];
				
		mCPUUsage[CurCPU] = (Total - Fields[3] - Fields[4]) / Total;
		mCPUUsageAvg[CurCPU].push(mCPUUsage[CurCPU]);
		
		// fire the event
		//onCPUUsage(
	} while (CurCPU < mCPUUsage.size());
}
