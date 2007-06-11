    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoLinuxInputDevice.hpp
*** \brief GizmoLinuxInputDevice class header
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

#ifndef __GizmoLinuxInputDevice_h
#define __GizmoLinuxInputDevice_h

#if HAVE_CONFIG_H
#include "config.h"
#endif


#include "../libH/DynamicBuffer.hpp"
#include "../libH/FileEventWatcher.hpp"
#include <linux/input.h>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/python/list.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoLinuxInputDevice
 * \brief Wrapper for functions dealing with Linux Input Event Interface Devices
 */
class GizmoLinuxInputDevice {
public:
	// public functions
	bool 				createEventPress(int Type, int Code); ///< Write a "press" event to the device (two events, with value 1, then 0)
	bool 				createEventPressMod(int Type, int Code, boost::python::object Modifiers); ///< Write event to the device with modifiers
	bool 				createEventRaw(int Type, int Code, int Value); ///< Write event to the device
	bool 				createEvents(int Type, int Code, int Value, int NumWrites); ///< Write multiple similar events to the device
	bool				getSendNullEvents() const;		///< Get whether or not the Gizmo sends NULL events
	bool 				grabExclusiveAccess(bool Grab); ///< Grab a device for exlusive access (or ungrab)
	bool				processEvent();			///< Should we process the event based on the minimum time between events?
	bool 				remapKey(int CurCode, int NewCode); /// Remap a key on the device
	void				setMinimumTimeBetweenEvents(float Seconds); ///< Set the minimum time between events
	void				setSendNullEvents(bool SendNull); ///< Set whether or not the Gizmo sends NULL events

	// construction / deconstruction
	GizmoLinuxInputDevice();					///< Serialize Constructor
	GizmoLinuxInputDevice(const H::DeviceInfo & DeviceInfo);	///< Default Constructor
	virtual ~GizmoLinuxInputDevice();				///< Destructor

	// static public functions
	static void			buildInputEventsVectorFromBuffer(std::vector<struct input_event> & EventVector, H::DynamicBuffer<char> const & Buffer); ///< Build an event list from a read buffer

protected:
	// protected functions
	
	// protected member variables
	H::DeviceInfo 			mDeviceInfo;			///< Info about the device
	unsigned long			mLastEventTime;			///< Time of last event
	unsigned long 			mMinTimeBetweenEvents;		///< Minimum time between events (smooth out trigger happy controllers)
	bool				mSendNullEvents;		///< Send NULL events if the device creates them?
	
private:
	// private functions
	
	// private member variables
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & mDeviceInfo;
		ar & mLastEventTime;
		ar & mMinTimeBetweenEvents;
		ar & mSendNullEvents;
	}			
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __GizmoLinuxInputDevice_h
