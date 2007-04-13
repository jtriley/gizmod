    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEvent.hpp
*** \brief GizmoEvent class header
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

#ifndef __GizmoEvent_h
#define __GizmoEvent_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "../libH/DynamicBuffer.hpp"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEvent
 * \brief Base class of all GizmoEvents
 *
 * This class is the base of all GizmoEvents attached to the system.
 * Each gizmo must inherit this class
 */
class GizmoEvent {
public:
	// public functions
	virtual std::string		getEventType();			///< Get the type of the Event
	
	// construction / deconstruction
	GizmoEvent();							///< Default Constructor
	virtual ~GizmoEvent();						///< Destructor
	
protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoEvent_h
