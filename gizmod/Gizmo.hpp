    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Gizmo.hpp
*** \brief Gizmo class header
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

#include "GizmoEvent.hpp"
#include "GizmoKeyDefs.hpp"
#include "../libH/FileEventWatcher.hpp"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

/**
 * \enum  GizmoClass
 * \brief These values tell GizmoDaemon what classes to use to represent the devices
 *
 * These values are repsented in Python by the same extension, under the enum class GizmoClass
 * For example: Gizmod.GizmoClass.Standard, and Gizmod.GizmoClass.Powermate
 *
 * GIZMO_CLASS_CPU is used with the CPU Usage device
 * GIZMO_CLASS_LIRC is used with LIRC (Infrared) devices (such as remote controls)
 * GIZMO_CLASS_POWERMATE is the class used for Griffin PowerMate, and SoundKnob devices
 * GIZMO_CLASS_SOUNDCARD is used for sound card events
 * GIZMO_CLASS_STANDARD is the default class and is used for all devices except ones with
 * 	special handlers
 */
typedef enum {
	GIZMO_CLASS_CPU,
	GIZMO_CLASS_LIRC,
	GIZMO_CLASS_POWERMATE,
	GIZMO_CLASS_SOUNDCARD,
	GIZMO_CLASS_STANDARD
} GizmoClass;
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Gizmo
 * \brief Base class of all Gizmos
 *
 * This class is the base of all Gizmos attached to the system.
 * Each Gizmo must inherit this class
 */
class Gizmo : public H::DeviceInfo {
public:
	// public functions
	GizmoClass			getGizmoClass();		///< Get the class of the Gizmo
	int				getGizmoKeyState(GizmoKey Key);	///< Get a key state
	virtual std::string		getGizmoType();			///< Get the type of the Gizmo
	virtual void			processEvent(GizmoEvent * pEvent); ///< Process an event
	void				setGizmoKeyState(GizmoKey Key, int State); ///< Set a keystate of the Gizmo
	
	// construction / deconstruction
	Gizmo(GizmoClass Class, const H::DeviceInfo & deviceInfo);	///< Default Constructor
	virtual ~Gizmo();						///< Destructor

protected:
	// private functions
	
	// private member variables
	GizmoClass			mClass;				///< Class of the Gizmo
	int				mKeyState[GIZMO_KEY_MAX];	///< Gizmos's key states
};

#endif // __Gizmo_h
