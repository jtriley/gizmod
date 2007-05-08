    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEvent.cpp
*** \brief GizmoEvent class body
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

#include "GizmoEvent.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoEvent Default Constructor
 */
GizmoEvent::GizmoEvent(GizmoEventClass Class) {
	mClass = Class;
}

/**
 * \brief GizmoEvent Serialize Constructor
 */
GizmoEvent::GizmoEvent() {
	mClass = GIZMO_EVENTCLASS_STANDARD;
}

/**
 * \brief GizmoEvent Destructor
 */
GizmoEvent::~GizmoEvent() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the class of Gizmo
 * \return GizmoClass of the Gizmo
 * 
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".GizmoClass"
 */
GizmoEventClass GizmoEvent::getClass() {
	return mClass;
}
