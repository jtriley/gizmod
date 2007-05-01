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
GizmoLinuxInputDevice::GizmoLinuxInputDevice(int FD) {
	mFD = FD;
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
 * \brief  Create an event on the device
 * \param  Type GizmoEventType of the event
 * \param  Code GizmoKey (or other code) of the event
 * \param  Value Value of the event
 * \return True on success
 *
 * Note: Writes the event, and a NULL event to signal a refresh
 */
bool GizmoLinuxInputDevice::createEvent(int Type, int Code, int Value) {
	struct input_event ev[2];
	memset(&ev, 0, sizeof(struct input_event) * 2);
	ev[0].type = Type;
	ev[0].code = Code;
	ev[0].value = Value;
	if (write(mFD, &ev, sizeof(struct input_event) * 2) == -1)
		return false;
	return true;
}

/**
 * \brief  Create a key press event on the device
 * \param  Type GizmoEventType of the event
 * \param  Code GizmoKey (or other code) of the event
 * \return True on success
 *
 * This creates two events, to simulate a key press
 * First send event with value 1, then value 0
 */
bool GizmoLinuxInputDevice::createEventPress(int Type, int Code) {
	if (!createEvent(Type, Code, 1))
		return false;
	if (!createEvent(Type, Code, 0))
		return false;
	return true;
}

/**
 * \brief  Create multiple events on the device
 * \param  Type GizmoEventType of the event
 * \param  Code GizmoKey (or other code) of the event
 * \param  Value Value of the event
 * \param  NumWrites Number of time to write the event (default == 1)
 * \return True on success
 *
 * Note: Writes the events, then a NULL event to signal a refresh
 */
bool GizmoLinuxInputDevice::createEvents(int Type, int Code, int Value, int NumWrites) {
	struct input_event ev;
	memset(&ev, 0, sizeof(struct input_event));
	ev.type = Type;
	ev.code = Code;
	ev.value = Value;
	for (int lp = 0; lp < NumWrites; lp ++) 
		if (write(mFD, &ev, sizeof(struct input_event)) == -1)
			return false;
	memset(&ev, 0, sizeof(struct input_event));
	if (write(mFD, &ev, sizeof(struct input_event)) == -1)
		return false;
	return true;
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
