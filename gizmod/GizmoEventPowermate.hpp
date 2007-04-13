    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventPowermate.hpp
*** \brief GizmoEventPowermate class header
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

#ifndef __GizmoEventPowermate_h
#define __GizmoEventPowermate_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEvent.hpp"
#include "GizmoPowermate.hpp"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEventPowermate
 * \brief Class for Powermate events
 *
 * This class is for all GizmoEventPowermates attached to the system.
 */
class GizmoEventPowermate : public GizmoEvent {
public:
	// public functions
	std::string			getEventType();			///< Get the type of the Event
	
	// construction / deconstruction
	GizmoEventPowermate();						///< Default Constructor
	virtual ~GizmoEventPowermate();					///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoEventPowermate_h
