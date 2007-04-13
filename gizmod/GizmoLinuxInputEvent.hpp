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

#include "../libH/DynamicBuffer.hpp"
#include <linux/input.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

typedef struct GizmoTimeVal {
	unsigned int Seconds;
	unsigned int MicroSeconds;
};
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoLinuxInputEvent
 * \brief Wrapper for functions dealing with Linux Input Event Interface Devices
 */
class GizmoLinuxInputEvent {
public:
	// public member variables
	unsigned short			RawType;				///< Raw type of the event
	unsigned short			RawCode;				///< Raw code of the event
	int				RawValue;				///< Raw value of the event
	GizmoTimeVal			TimeStamp;				///< Time stamp of the event
	
	// public functions

	// construction / deconstruction
	GizmoLinuxInputEvent();							///< Default Constructor
	GizmoLinuxInputEvent(struct input_event const & InputEvent);		///< Init Constructor
	virtual ~GizmoLinuxInputEvent();					///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoLinuxInputEvent_h
