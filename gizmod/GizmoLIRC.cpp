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
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/UtilTime.hpp"
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
// Type Defs
///////////////////////////////////////

float GizmoLIRC::mMinTimeBetweenEvents = 0.15f;

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoLIRC Default Constructor
 */
GizmoLIRC::GizmoLIRC(const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID) : Gizmo(GIZMO_CLASS_LIRC, deviceInfo, DeviceID, DeviceClassID)  {
	mLastEventTime = UtilTime::getTicks();
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
std::string GizmoLIRC::getType() {
	return GIZMO_LIRC_TYPE;
}

/**
 * \brief  Process an event
 * \param  pEvent The event to process
 * \return True on if the event should get passed on to the script
*/
bool GizmoLIRC::processEvent(GizmoEvent * pEvent) {
	float TimeBetweenEvents = float(UtilTime::getTicks() - mLastEventTime) / 1000000.0f;
	if (TimeBetweenEvents <= mMinTimeBetweenEvents)
		return false;
	cdbg5 << "LIRC Time Between Events: " << TimeBetweenEvents << " Seconds" << endl;
	mLastEventTime = UtilTime::getTicks();
	return true;
}

/**
 * \brief  Set the minimum time between events
 * \param  Seconds The time in seconds
 *
 * This is for remotes that are a bit jittery, or trigger happy.
 * Set this to an appropriate value (issue -V 5 to see the timings)
 */
void GizmoLIRC::setMinimumTimeBetweenEvents(float Seconds) {
	mMinTimeBetweenEvents = Seconds;
}
