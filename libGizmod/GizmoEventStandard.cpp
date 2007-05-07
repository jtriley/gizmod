    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventStandard.cpp
*** \brief GizmoEventStandard class body
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

#include "GizmoEventStandard.hpp"
#include "GizmoLinuxInputDevice.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/Util.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

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
 * \brief GizmoEventStandard Default Constructor
 */
GizmoEventStandard::GizmoEventStandard() : GizmoEvent(GIZMO_EVENTCLASS_STANDARD) {
}

/**
 * \brief GizmoEventStandard Init Constructor
 */
GizmoEventStandard::GizmoEventStandard(struct input_event const & InputEvent) : GizmoEvent(GIZMO_EVENTCLASS_STANDARD), GizmoLinuxInputEvent(InputEvent) {
}

/**
 * \brief GizmoEventStandard Destructor
 */
GizmoEventStandard::~GizmoEventStandard() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Build an event vector from a read buffer
 * \param  EventVector Reference to a vector which will contain the results
 * \param  Buffer The bufer to convert into events
 * \param  SendNullEvents Signals if NULL events should be passed onto the config script
 */
void GizmoEventStandard::buildEventsVectorFromBuffer(std::vector< boost::shared_ptr<GizmoEventStandard> > & EventVector, H::DynamicBuffer<char> const & Buffer, bool SendNullEvents) {
	std::vector<struct input_event> InputEvents;
	GizmoLinuxInputDevice::buildInputEventsVectorFromBuffer(InputEvents, Buffer);
	apply_static_func_args(InputEvents, GizmoEventStandard::buildEventsVectorFromBufferFunctor, &EventVector, SendNullEvents);
}

/**
 * \brief  Functor for building events from Linnux input_events
 */
void GizmoEventStandard::buildEventsVectorFromBufferFunctor(struct input_event & InputEvent, std::vector< boost::shared_ptr<GizmoEventStandard> > * pEventVector, bool SendNullEvents) {
	if ( (!SendNullEvents) && (InputEvent.type == 0) && (InputEvent.code == 0) && (InputEvent.value == 0) )
		return;
	pEventVector->push_back(boost::shared_ptr<GizmoEventStandard>(new GizmoEventStandard(InputEvent)));
}
