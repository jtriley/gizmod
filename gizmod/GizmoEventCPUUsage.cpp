    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventCPUUsage.cpp
*** \brief GizmoEventCPUUsage class body
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

#include "GizmoEventCPUUsage.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoEventCPUUsage Default Constructor
 */
GizmoEventCPUUsage::GizmoEventCPUUsage(std::vector<double> const & Usages, std::vector<double> const & Averages) : 
	GizmoEvent(GIZMO_EVENTCLASS_CPUUSAGE),
	mAverages(Averages),
	mUsages(Usages)
{
}

/**
 * \brief GizmoEventCPUUsage Destructor
 */
GizmoEventCPUUsage::~GizmoEventCPUUsage() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the CPU Usage for CPU at the specified Index
 * \param  CPUIndex The CPU in question  (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
 */
double GizmoEventCPUUsage::getCPUUsage(size_t CPUIndex) {
	if (CPUIndex < 0.0)
		return 0.0;
	else if (CPUIndex >= mUsages.size())
		return 0.0;
	return mUsages[CPUIndex];
}

/**
 * \brief  Get the CPU Usage for CPU at the specified Index
 * \param  CPUIndex The CPU in question  (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
 */
double GizmoEventCPUUsage::getCPUUsageAvg(size_t CPUIndex) {
	if (CPUIndex < 0.0)
		return 0.0;
	else if (CPUIndex >= mAverages.size())
		return 0.0;
	return mAverages[CPUIndex];
}

/**
 * \brief  Get the number of CPUs the event is describing
 * \return Number of CPUs
 */
size_t GizmoEventCPUUsage::getNumCPUs() {
	return mUsages.size();
}

