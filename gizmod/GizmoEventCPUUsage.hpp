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
#include "CPUUsage.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

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
	double				getCPUUsage(size_t CPUIndex) const; 	///< Get the CPU Usage for CPU at the specified Index (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
	double				getCPUUsageAvg(size_t CPUIndex) const;	///< Get the Averaged CPU Usage for CPU at the specified Index (0 for ALL cpus, 1 for CPU1, 2 for CPU2, etc)
	size_t				getNumCPUs() const;			///< Get the number of CPUs
	
	// construction / deconstruction
	GizmoEventCPUUsage(); 							///< Default Constructor
	GizmoEventCPUUsage(std::vector< boost::shared_ptr<CPUUsageInfo> > const & Event); ///< Default Constructor
	virtual ~GizmoEventCPUUsage();						///< Destructor

protected:
	// private functions
	
	// private member variables
	std::vector< boost::shared_ptr<CPUUsageInfo> > mEvent;			///< The Raw Event info
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<GizmoEvent>(*this);
		ar & mEvent;
	}	
};

#endif // __GizmoEventCPUUsage_h
