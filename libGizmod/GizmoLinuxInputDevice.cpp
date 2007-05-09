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
#include "../libH/UtilTime.hpp"

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
GizmoLinuxInputDevice::GizmoLinuxInputDevice(const H::DeviceInfo & DeviceInfo) {
	mDeviceInfo = DeviceInfo;
	mSendNullEvents = false;
	mLastEventTime = 0;
	mMinTimeBetweenEvents = 0;
}

/**
 * \brief GizmoLinuxInputDevice Serialize Constructor
 */
GizmoLinuxInputDevice::GizmoLinuxInputDevice() {
	mSendNullEvents = false;
	mLastEventTime = 0;
	mMinTimeBetweenEvents = 0;
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
 * See GizmoKeyDefs.hpp for a list of the available Types, and Codes
 * 
 * The Value field can mean many things, however for key press events
 * a Value of 1 means turn the key "on", and 0 means turn the key "off"
 *
 * Note: Writes the event, and a NULL event to signal a refresh
 */
bool GizmoLinuxInputDevice::createEvent(int Type, int Code, int Value) {
	struct input_event ev[2];
	memset(&ev, 0, sizeof(struct input_event) * 2);
	ev[0].type = Type;
	ev[0].code = Code;
	ev[0].value = Value;
	if (write(mDeviceInfo.FileDescriptor, &ev, sizeof(struct input_event) * 2) == -1)
		return false;
	return true;
}

/**
 * \brief  Create a key press event on the device
 * \param  Type GizmoEventType of the event
 * \param  Code GizmoKey (or other code) of the event
 * \return True on success
 *
 * See GizmoKeyDefs.hpp for a list of the available Types, and Codes
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
 * See GizmoKeyDefs.hpp for a list of the available Types, and Codes
 * 
 * The Value field can mean many things, however for key press events
 * a Value of 1 means turn the key "on", and 0 means turn the key "off"
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
		if (write(mDeviceInfo.FileDescriptor, &ev, sizeof(struct input_event)) == -1)
			return false;
	memset(&ev, 0, sizeof(struct input_event));
	if (write(mDeviceInfo.FileDescriptor, &ev, sizeof(struct input_event)) == -1)
		return false;
	return true;
}

/**
 * \brief  Get whether or not the Gizmo sends NULL events
 * \return True if sends null events
 */
bool GizmoLinuxInputDevice::getSendNullEvents() const {
	return mSendNullEvents;
}

/** 
 * \brief  Set a device's exlusive access property
 * \param  Grab Enable exlusive access if Grab is true
 * \return True on success
 *
 * When a device is in exlusive access mode only gizmod will
 * receive events from it.  This allows intercepting the events
 * without the rest of the system knowing about them, and they
 * can then be translated into other events by issuing createEvent calls
 */
bool GizmoLinuxInputDevice::grabExclusiveAccess(bool Grab) {
	if (ioctl(mDeviceInfo.FileDescriptor, EVIOCGRAB, Grab ? 1 : 0)) {
		cerr << "Device [" << mDeviceInfo.DeviceName <<"] Exclusive Access Grab Failed!" << endl;
		return false;
	}

	cdbg << "Device [" << mDeviceInfo.DeviceName <<"] Exclusive Access Granted" << endl;
	return true;
}

/**
 * \brief  Should we process the event based on the minimum time between events?
 * \return True if we should, false if not
 */
bool GizmoLinuxInputDevice::processEvent() {
	if (UtilTime::getTicks() - mLastEventTime < mMinTimeBetweenEvents)
		return false;
	mLastEventTime = UtilTime::getTicks();
	return true;
}

/**
 * \brief  Remap a key on the input device
 * \param  CurCode Key to change the mapping of
 * \param  NewCode New code of the key
 * \return True on success
 */
bool GizmoLinuxInputDevice::remapKey(int CurCode, int NewCode) {
	int codes[2];
	codes[0] = CurCode;
	codes[1] = NewCode;
	if (ioctl(mDeviceInfo.FileDescriptor, EVIOCSKEYCODE, codes)) {
		cerr << "Device [" << mDeviceInfo.DeviceName <<"] Failed to Remap Key [" << CurCode << "]" << " to [" << NewCode << "]" << endl;
		return false;
	}

	cdbg << "Device [" << mDeviceInfo.DeviceName <<"] Key [" << CurCode << "]" << " Remapped to [" << NewCode << "]" << endl;
	return true;
}

/**
 * \brief  Set the minimum time between events
 * \param  Seconds The time in seconds
 *
 * This is for remotes that are a bit jittery, or trigger happy.
 * Set this to an appropriate value (issue -V 5 to see the timings)
 */
void GizmoLinuxInputDevice::setMinimumTimeBetweenEvents(float Seconds) {
	mMinTimeBetweenEvents = (long) (Seconds * 1000000.0f);
}

/**
 * \brief  Set whether or not the Gizmo sends NULL events
 * \param  SendNull Set to true if the device should send NULL events
 */
void GizmoLinuxInputDevice::setSendNullEvents(bool SendNull) {
	mSendNullEvents = SendNull;
}
