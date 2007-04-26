    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoSoundCard.hpp
*** \brief GizmoSoundCard class header
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

#ifndef __GizmoSoundCard_h
#define __GizmoSoundCard_h

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
 * \class GizmoSoundCard
 * \brief SoundCard Gizmo
 *
 * This class contains all of the helper functions for making use of SoundCardUsage
 */
class GizmoSoundCard : public Gizmo {
public:
	// public functions
	std::string			getGizmoType();				///< Get the type of the Gizmo
	
	// construction / deconstruction
	GizmoSoundCard(const H::DeviceInfo & deviceInfo);			///< Default Constructor
	virtual ~GizmoSoundCard();						///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoSoundCard_h
