    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoLIRC.cpp
*** \brief GizmoLIRC class body
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

#include "GizmoLIRC.hpp"
//#include "GizmoEventLIRC.hpp"
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
 * \def   GIZMO_LIRC_TYPE
 * \brief String type of this gizmo
 */
#define GIZMO_LIRC_TYPE	"LIRC"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoLIRC Default Constructor
 */
GizmoLIRC::GizmoLIRC(const H::DeviceInfo & deviceInfo) : Gizmo(GIZMO_CLASS_LIRC, deviceInfo)  {
}

/**
 * \brief GizmoLIRC Destructor
 */
GizmoLIRC::~GizmoLIRC() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the type of this Gizmo
 * \return Type of the Gizmo
 */
std::string GizmoLIRC::getGizmoType() {
	return GIZMO_LIRC_TYPE;
}

/**
 * \brief  Process an event
 * \param  pEvent The event to process
 */
void GizmoLIRC::processEvent(GizmoEvent * pEvent) {
	/*
	GizmoEventLIRC * pLIRCEvent = static_cast<GizmoEventLIRC *>(pEvent);
	
	switch (pLIRCEvent->Type) {
	case EV_KEY:
		setGizmoKeyState(pLIRCEvent->Code, pLIRCEvent->Value);
		break;
	default:
		// do nothing
		break;
	}
	*/
}
