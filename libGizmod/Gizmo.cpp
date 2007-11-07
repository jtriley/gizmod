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

#include "Gizmo.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;
using namespace Gizmod;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def   GIZMO_TYPE_UNSPECIFIED
 * \brief String returned if a super class failed to reimplement getGizmoType
**/
#define GIZMO_TYPE_UNSPECIFIED	"Unspecified"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Gizmo Default Constructor
**/
Gizmo::Gizmo(GizmoClass Class, const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID) : DeviceInfo(deviceInfo) {
	mClass = Class;
	mDeviceID = DeviceID;
	mDeviceClassID = DeviceClassID;
	memset(mKeyState, 0, sizeof(int) * GIZMO_KEY_MAX);
}

/**
 * \brief Gizmo Serialize Constructor
**/
Gizmo::Gizmo() {
}

/**
 * \brief Gizmo Destructor
**/
Gizmo::~Gizmo() {
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
**/
GizmoClass Gizmo::getClass() {
	return mClass;
}

/**
 * \brief  Get the Device ID
 * \return The Device ID
 *
 * This is the unique Device ID of the Gizmo
**/
int Gizmo::getDeviceID() {
	return mDeviceID;
}

/**
 * \brief  Get the Device Class ID
 * \return The Device Class ID
 *
 * Each Gizmo in this GizmoClass will have an ID that is unique only amongst this class.
 *
 * Effectively this can be used to find out which Powermate device an event belongs to, and so forth.
**/
int Gizmo::getDeviceClassID() {
	return mDeviceClassID;
} 

/**
 * \brief  Get the class of the Gizmo
 * \param  Key The key to inquire upon
 * \return The value of the button (0 == off, 1 == on, 2 == repeating)
**/
int Gizmo::getKeyState(GizmoKey Key) {
	return mKeyState[Key];
}

/**
 * \brief  Get the type of Gizmo
 * \return Type of the Gizmo
 *
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".GizmoType"
**/
std::string Gizmo::getType() {
	return GIZMO_TYPE_UNSPECIFIED;
}

/**
 * \brief  Process an event
 * \param  pEvent The event to process
 * \return True on if the event should get passed on to the script
**/
bool Gizmo::processEvent(GizmoEvent * pEvent) {
	// override me
	return true;
}

/**
 * \brief  Set a keystate of the Gizmo
 * \param  Key The key to change states
 * \param  State The new state (0 == off, 1 == on, 2 == repeating)
**/
void Gizmo::setKeyState(GizmoKey Key, int State) {
	mKeyState[Key] = State;
}
