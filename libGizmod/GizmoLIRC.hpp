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
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

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
	void				setDisableFirstRepeats(int Repeats); ///< Set the number of repeats to disable
	void				setMinimumTimeBetweenEvents(float Seconds); ///< Set the minimum time between events
	
	// construction / deconstruction	
	GizmoLIRC();						///< Serialize Constructor
	GizmoLIRC(const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID); ///< Default Constructor
	virtual ~GizmoLIRC();					///< Destructor
	
protected:
	// protected functions
	
	// protected member variables
	int				mDisabledRepeats;	///< Number of disabled repeats
	long				mLastEventTime;		///< Time of last event
	float				mMinTimeBetweenEvents;	///< Minimum time between events (smooth out trigger happy controllers)

private:
	// private functions
	
	// private member variables
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Gizmo>(*this);
		ar & mDisabledRepeats;
		ar & mLastEventTime;
		ar & mMinTimeBetweenEvents;
	}		
};

#endif // __GizmoLIRC_h
