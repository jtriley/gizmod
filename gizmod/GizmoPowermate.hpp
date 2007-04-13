    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoPowermate.hpp
*** \brief GizmoPowermate class header
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

#ifndef __GizmoPowermate_h
#define __GizmoPowermate_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Gizmo.hpp"
#include "GizmoLinuxInputDevice.hpp"

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoPowermate
 * \brief Powermate Gizmo
 *
 * This class contains all of the helper functions for making use of the Powermate
 */
class GizmoPowermate : public Gizmo, public GizmoLinuxInputDevice {
public:
	// public functions
	unsigned char			getLEDValue();			///< Get the Powermate's LED value
	std::string			getGizmoType();			///< Get the type of the Gizmo
	
	// construction / deconstruction	
	GizmoPowermate(const H::DeviceInfo & deviceInfo);		///< Default Constructor
	virtual ~GizmoPowermate();					///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoPowermate_h
