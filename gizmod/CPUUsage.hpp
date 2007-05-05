    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  CPUUsage.hpp
*** \brief CPUUsage class header
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

#ifndef __CPUUsage_h
#define __CPUUsage_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "../libH/Average.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////////////////
// Typedefs / enums
///////////////////////////////////////

/**
 * \enum   ProcStatField
 * \brief  Enumeration to match /proc/stat
 */
typedef enum {
	CPUUSAGE_USER		= 0,
	CPUUSAGE_NICE 		= 1,
	CPUUSAGE_SYSTEM		= 2,
	CPUUSAGE_IDLE 		= 3,
	CPUUSAGE_IOWAIT 	= 4,
	CPUUSAGE_IRQ 		= 5,
	CPUUSAGE_SOFTIRQ 	= 6,
	CPUUSAGE_RESERVED 	= 7,
	CPUUSAGE_MAX 
} ProcStatField;

/**
 * \struct CPUUsageInfo
 * \brief  Structure that holds info about each CPU
 */
struct CPUUsageInfo {
	double 				Field[CPUUSAGE_MAX];		///< CPU Usage fields
	double 				Stat[CPUUSAGE_MAX];		///< CPU Stat fields
	double 				Usage;
	H::Average			Averager;
};

//////////////////////////////////////////////////////////////////////////////
// CPUUsage Class Definition
///////////////////////////////////////

/**
 * \class CPUUsage
 * \brief CPU Usage monitor
 */
class CPUUsage {
public:
	// public functions
	size_t 				getNumCPUs();			///< Get the number of CPUs on the system
	void 				init();				///< Start watching!
	virtual void			onCPUUsage(std::vector< boost::shared_ptr<CPUUsageInfo> > const & Event); ///< Event triggered when CPU Usage stats are updated
	void				setTimeBetweenUpdates(float Seconds); ///< Time between updates in seconds

	// construction / deconstruction
	CPUUsage();							///< Default Constructor
	virtual ~CPUUsage();						///< Destructor

private:
	// private functions
	void				shutdown();			///< Shutodwn the CPU Usage monitor
	void				threadProc();			///< The thread procedure loop
	void				updateUsageStats();		///< Force an update of the CPU Usage stats
	
	// private member variables
	float				mSecsBetweenUpdates;		///< Time between updates
	bool				mWatching;			///< Continue watching for usage events
	std::vector< boost::shared_ptr<CPUUsageInfo> > mCPUUsage;	///< CPU Usage info
	
	/**
	 * Thread callback procedure struct
	 */
	struct CPUUsageThreadProc {
		CPUUsageThreadProc(CPUUsage * pCPUUsage) : mpCPUUsage(pCPUUsage) {
			mpCPUUsage->mThreading = false;
		};
		
		/// Thread proc
		void operator()() {
			mpCPUUsage->mThreading = true;
			mpCPUUsage->threadProc();
			mpCPUUsage->mThreading = false;
		}
		
		CPUUsage * 		mpCPUUsage;			///< The associated SoundCard
	};		
	bool				mThreading;			///< Variable to keep track if we're threading or not
	CPUUsageThreadProc		mThreadProc;			///< The thread procedure instance	
};

#endif // __CPUUsage_h
