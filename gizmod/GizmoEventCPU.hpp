    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventCPU.hpp
*** \brief GizmoEventCPU class header
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

#ifndef __GizmoEventCPU_h
#define __GizmoEventCPU_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEvent.hpp"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEventCPU
 * \brief Base class of all GizmoEventCPUs
 *
 * This class is the base of all GizmoEventCPUs attached to the system.
 * Each GizmoEventCPU must inherit this class
 */
class GizmoEventCPU : public GizmoEvent {
public:
	// public functions
	std::string			getEventType();			///< Get the type of the Event
	
	// construction / deconstruction
	GizmoEventCPU();						///< Default Constructor
	virtual ~GizmoEventCPU();					///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoEventCPU_h
