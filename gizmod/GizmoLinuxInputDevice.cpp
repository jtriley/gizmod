    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoLinuxInputDevice.cpp
*** \brief GizmoLinuxInputDevice class body
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

#include "GizmoLinuxInputDevice.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoLinuxInputDevice Default Constructor
 */
GizmoLinuxInputDevice::GizmoLinuxInputDevice() {
	mSendNullEvents = false;
}

/**
 * \brief GizmoLinuxInputDevice Destructor
 */
GizmoLinuxInputDevice::~GizmoLinuxInputDevice() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Build an event vector from a read buffer
 * \param  EventVector Reference to a vector which will contain the results
 * \param  Buffer The bufer to convert into events
 */
void GizmoLinuxInputDevice::buildInputEventsVectorFromBuffer(std::vector<struct input_event> & EventVector, H::DynamicBuffer<char> const & Buffer) {
	DynamicBufferConverter<char, struct input_event>::convert(EventVector, Buffer);
}

/**
 * \brief  Get whether or not the Gizmo sends NULL events
 * \return True if sends null events
 */
bool GizmoLinuxInputDevice::getSendNullEvents() {
	return mSendNullEvents;
}

/**
 * \brief  Set whether or not the Gizmo sends NULL events
 * \param  SendNull Set to true if the device should send NULL events
 */
void GizmoLinuxInputDevice::setSendNullEvents(bool SendNull) {
	mSendNullEvents = SendNull;
}
