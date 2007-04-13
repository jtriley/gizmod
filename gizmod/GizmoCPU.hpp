    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoCPU.hpp
*** \brief GizmoCPU class header
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

#ifndef __GizmoCPU_h
#define __GizmoCPU_h

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
 * \class GizmoCPU
 * \brief CPU Gizmo
 *
 * This class contains all of the helper functions for making use of CPUUsage
 */
class GizmoCPU : public Gizmo {
public:
	// public functions
	std::string			getGizmoType();			///< Get the type of the Gizmo
	
	// construction / deconstruction
	GizmoCPU();							///< Default Constructor
	virtual ~GizmoCPU();						///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __GizmoCPU_h
