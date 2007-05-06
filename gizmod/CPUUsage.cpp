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
#define DEFAULT_UPDATE_DELAY	0.1f

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
	mThreading = false;
	getNumCPUs();
}

/**
 * \brief CPUUsageInfo Default Constructor
 */
CPUUsageInfo::CPUUsageInfo() {
	memset(Field, 0, sizeof(double) * CPUUSAGE_MAX);
	memset(Stat, 0, sizeof(double) * CPUUSAGE_MAX);	
	Usage = 0.0;
	Average = 0.0;
}

/**
 * \brief CPUUsage Destructor
 */
CPUUsage::~CPUUsage() {
	shutdown();
}

/**
 * \brief CPUUsageInfo Destructor
 */
CPUUsageInfo::~CPUUsageInfo() {
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
		for (int lp = 0; lp < cpus; lp ++)
			mCPUUsage[lp] = shared_ptr<CPUUsageInfo>(new CPUUsageInfo);
	}
	
	return mCPUUsage.size() - 1;
}

/**
 * \brief  Start the Usage watcher thread
 */
void CPUUsage::init() {
	if (getNumCPUs() < 0) {
		cdbg << "Cannot give CPU Usage Stats! -- Cannot access [" << PROC_STAT_PATH << "]" << endl;
		return;
	}
	
	// initialize the event handler thread
	thread thrd(mThreadProc);
}

/**
 * \brief  Event triggered when CPU Usage stats are updated
 * \param  Event A vector of CPU Usage info, where index 0 is ALL processors, 1 is proc 1, 2 is cpu 2, etc
 */
void CPUUsage::onCPUUsage(std::vector< boost::shared_ptr<CPUUsageInfo> > const & Event) {
	// override me
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
	while (mThreading) {
		cdbg5 << "Waiting on CPUUsage Thread to Finish..." << endl;
		UtilTime::sleep(0.1f);
	}
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
	// open the file
	FILE * StatFile;
	if ((StatFile = fopen(PROC_STAT_PATH, "r")) == NULL) {
		cdbg << "Failed get CPU Usage Information" << endl;
		return;
	}

	// read and close
	for (size_t cpu = 0; cpu < mCPUUsage.size(); cpu ++) {
		double Info[CPUUSAGE_MAX];
		int CpuIndex = 0;
		shared_ptr<CPUUsageInfo> pUsage = mCPUUsage[cpu];
		if (cpu == 0)
			fscanf(StatFile, "cpu %lf %lf %lf %lf %lf %lf %lf %lf\n", Info, Info + 1, Info + 2, Info + 3, Info + 4, Info + 5, Info + 6, Info + 7);
		else {
			fscanf(StatFile, "cpu%d %lf %lf %lf %lf %lf %lf %lf %lf\n", &CpuIndex, Info, Info + 1, Info + 2, Info + 3, Info + 4, Info + 5, Info + 6, Info + 7);
		}
		
		// calculate the total
		double Total = 0.0;
		for (int lp = 0; lp < CPUUSAGE_MAX; lp ++) {
			//Total 
			pUsage->Field[lp] = Info[lp] - pUsage->Stat[lp];
			Total += pUsage->Field[lp];
			pUsage->Stat[lp] = Info[lp];
		} 
		pUsage->Usage = ((Total - pUsage->Field[CPUUSAGE_IDLE] - pUsage->Field[CPUUSAGE_IOWAIT]) / Total) * 100.0;
		pUsage->mAverager.push(pUsage->Usage);
		pUsage->Average = pUsage->mAverager.average();
	}
	fclose(StatFile);

	// fire the event
	onCPUUsage(mCPUUsage);
}
