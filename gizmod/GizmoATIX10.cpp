    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoATIX10.cpp
*** \brief GizmoATIX10 class body
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

#include "GizmoATIX10.hpp"
#include "GizmoEventATIX10.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def   GIZMO_ATIX10_TYPE
 * \brief String type of this gizmo
 */
#define GIZMO_ATIX10_TYPE	"ATIX10"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoATIX10 Default Constructor
 */
GizmoATIX10::GizmoATIX10(const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID) : Gizmo(GIZMO_CLASS_ATIX10, deviceInfo, DeviceID, DeviceClassID), GizmoLinuxInputDevice(deviceInfo.FileDescriptor) {
}

/**
 * \brief GizmoATIX10 Destructor
 */
GizmoATIX10::~GizmoATIX10() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the type of this Gizmo
 * \return Type of the Gizmo
 */
std::string GizmoATIX10::getType() {
	return GIZMO_ATIX10_TYPE;
}

/**
 * \brief  Process an event
 * \param  pEvent The event to process
 * \return True on if the event should get passed on to the script
 */
bool GizmoATIX10::processEvent(GizmoEvent * pEvent) {
	GizmoEventATIX10 * pATIX10Event = static_cast<GizmoEventATIX10 *>(pEvent);
	
	switch (pATIX10Event->Type) {
	case EV_KEY:
		setKeyState(pATIX10Event->Code, pATIX10Event->Value);
		break;
	default:
		// do nothing
		break;
	}
	
	return true;
}
