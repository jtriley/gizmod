    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventCPUUsage.hpp
*** \brief GizmoEventCPUUsage class header
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

#ifndef __GizmoEventCPUUsage_h
#define __GizmoEventCPUUsage_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEvent.hpp"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEventCPUUsage
 * \brief Class for CPU events
 *
 * This class is for all GizmoEventCPUUsages attached to the system.
 */
class GizmoEventCPUUsage : public GizmoEvent {
public:
	// public functions
	double				getCPUUsage(size_t CPUIndex);	///< Get the CPU Usage for CPU at the specified Index (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
	double				getCPUUsageAvg(size_t CPUIndex);///< Get the Averaged CPU Usage for CPU at the specified Index (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
	size_t				getNumCPUs();			///< Get the number of CPUs
	
	// construction / deconstruction
	GizmoEventCPUUsage(std::vector<double> const & Usages, std::vector<double> const & Averages); ///< Default Constructor
	virtual ~GizmoEventCPUUsage();					///< Destructor

protected:
	// private functions
	
	// private member variables
	std::vector<double> const & 	mAverages;			///< Averaged CPU Usage vector (0 is all processors, 1 is processor 1, etc)
	std::vector<double> const & 	mUsages;			///< CPU Usage vector (0 is all processors, 1 is processor 1, etc)
};

#endif // __GizmoEventCPUUsage_h
