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
GizmoEventCPUUsage::GizmoEventCPUUsage(std::vector< boost::shared_ptr<CPUUsageInfo> > const & Event) : 
	GizmoEvent(GIZMO_EVENTCLASS_CPUUSAGE),
	mEvent(Event)
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
	else if (CPUIndex >= mEvent.size())
		return 0.0;
	return mEvent[CPUIndex]->Usage;
}

/**
 * \brief  Get the CPU Usage for CPU at the specified Index
 * \param  CPUIndex The CPU in question  (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
 */
double GizmoEventCPUUsage::getCPUUsageAvg(size_t CPUIndex) {
	if (CPUIndex < 0.0)
		return 0.0;
	else if (CPUIndex >= mEvent.size())
		return 0.0;
	return mEvent[CPUIndex]->Averager.average();
}

/**
 * \brief  Get the number of CPUs the event is describing
 * \return Number of CPUs
 */
size_t GizmoEventCPUUsage::getNumCPUs() {
	return mEvent.size();
}

