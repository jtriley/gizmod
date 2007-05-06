    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoLIRC.hpp
*** \brief GizmoLIRC class header
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

#ifndef __GizmoLIRC_h
#define __GizmoLIRC_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Gizmo.hpp"

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoLIRC
 * \brief LIRC Gizmos
 *
 * This class contains all of the helper functions for making use of LIRC devices
 */
class GizmoLIRC : public Gizmo {
public:
	// public functions
	virtual std::string		getType();		///< Get the type of the Gizmo
	virtual bool 			processEvent(GizmoEvent * pEvent); ///< Process an event
	
	// construction / deconstruction	
	GizmoLIRC();						///< Serialize Constructor
	GizmoLIRC(const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID); ///< Default Constructor
	virtual ~GizmoLIRC();					///< Destructor

	// static public functions
	static void			setMinimumTimeBetweenEvents(float Seconds); ///< Set the minimum time between events
	
protected:
	// protected functions
	
	// protected member variables
	unsigned long			mLastEventTime;		///< Time of last event
	static float			mMinTimeBetweenEvents;	///< Minimum time between events (smooth out trigger happy controllers)

private:
	// private functions
	
	// private member variables
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Gizmo>(*this);
		ar & mLastEventTime;
	}		
};

#endif // __GizmoLIRC_h
