    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Gizmo.cpp
*** \brief Gizmo class body
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

#ifndef __Gizmo_h
#define __Gizmo_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Gizmo
 * \brief Base class of all Gizmos
 *
 * This class is the base of all Gizmos attached to the system.
 * Each gizmo must inherit this class
 */
class Gizmo {
public:
	// public functions
	
	// construction / deconstruction
	Gizmo();					///< Default Constructor
	virtual ~Gizmo();				///< Destructor

protected:
	// private functions
	
	// private member variables
};

#endif // __Gizmo_h