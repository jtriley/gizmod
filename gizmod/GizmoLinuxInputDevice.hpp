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
#include <linux/input.h>
#include <vector>

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
	bool				getSendNullEvents();		///< Get whether or not the Gizmo sends NULL events
	void				setSendNullEvents(bool SendNull); ///< Set whether or not the Gizmo sends NULL events

	// construction / deconstruction
	GizmoLinuxInputDevice();					///< Default Constructor
	virtual ~GizmoLinuxInputDevice();				///< Destructor

	// static public functions
	static void			buildInputEventsVectorFromBuffer(std::vector<struct input_event> & EventVector, H::DynamicBuffer<char> const & Buffer); ///< Build an event list from a read buffer

protected:
	// private functions
	
	// private member variables
	bool				mSendNullEvents;		///< Send NULL events if the device creates them?
};

#endif // __GizmoLinuxInputDevice_h
