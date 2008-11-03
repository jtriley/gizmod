    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoLinuxInputEvent.hpp
*** \brief GizmoLinuxInputEvent class header
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

#ifndef __GizmoLinuxInputEvent_h
#define __GizmoLinuxInputEvent_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoKeyDefs.hpp"
#include "../libH/DynamicBuffer.hpp"
#include <linux/input.h>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

/**
 * \struct GizmoTimeVal
 * \brief  Wrapper for the C timeval struct (for exposure to Python)
**/
struct GizmoTimeVal {
	unsigned int Seconds;							///< Time in Seconds
	unsigned int MicroSeconds;						///< Time remaining (after Seconds) in MicroSeconds
	
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & Seconds;
		ar & MicroSeconds;
	}					
};
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoLinuxInputEvent
 * \brief Wrapper for functions dealing with Linux Input Event Interface Devices
**/
class GizmoLinuxInputEvent {
public:
	// public member variables
	unsigned short			RawType;				///< Raw type of the event
	unsigned short			RawCode;				///< Raw code of the event
	GizmoTimeVal			TimeStamp;				///< Time stamp of the event
	GizmoKey			Code;					///< Human decipherable code of the event
	GizmoEventType			Type;					///< Human decipherable type of the event
	int				Value;					///< Value of the event -- For Standard button events, this value will be 0 if a button is unpressed, 1 if pressed, and 2 if held and repeat events are generated
	
	// public functions

	// construction / deconstruction
	GizmoLinuxInputEvent();							///< Default Constructor
	GizmoLinuxInputEvent(struct input_event const & InputEvent);		///< Init Constructor
	virtual ~GizmoLinuxInputEvent();					///< Destructor

protected:
	// private functions
	
	// private member variables
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & RawType;
		ar & RawCode;
		ar & TimeStamp;
		ar & Code;
		ar & Type;
		ar & Value;
	}				
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __GizmoLinuxInputEvent_h
