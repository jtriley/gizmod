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
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

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
 * GIZMO_CLASS_ATIX10 is used with ATI X10 RF Remotes
 * GIZMO_CLASS_LIRC is used with LIRC (Infrared) devices (such as remote controls)
 * GIZMO_CLASS_POWERMATE is the class used for Griffin PowerMate, and SoundKnob devices
 * GIZMO_CLASS_STANDARD is the default class and is used for all devices except ones with
 * 	special handlers
 */
typedef enum {
	GIZMO_CLASS_ATIX10,
	GIZMO_CLASS_LIRC,
	GIZMO_CLASS_POWERMATE,
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
	virtual GizmoClass		getClass();			///< Get the class of the Gizmo
	int				getDeviceID();			///< Get the Device ID
	int				getDeviceClassID();		///< Get the Device Class ID
	virtual int			getKeyState(GizmoKey Key);	///< Get a key state
	virtual std::string		getType();			///< Get the type of the Gizmo
	virtual bool			processEvent(GizmoEvent * pEvent); ///< Process an event
	void				setKeyState(GizmoKey Key, int State); ///< Set a keystate of the Gizmo
	
	// construction / deconstruction
	Gizmo();							///< Serialize Constructor
	Gizmo(GizmoClass Class, const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID); ///< Default Constructor
	virtual ~Gizmo();						///< Destructor

protected:
	// protected functions
	
	// protected member variables
	GizmoClass			mClass;				///< Class of the Gizmo
	int 				mDeviceID;			///< Unique ID of the device
	int				mDeviceClassID;			///< ID of the device in its class
	int				mKeyState[GIZMO_KEY_MAX];	///< Gizmos's key states
	
private:
	// private functions
	
	// private member variables
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<H::DeviceInfo>(*this);
		ar & mClass;
		ar & mDeviceID;
		ar & mDeviceClassID;
		ar & mKeyState;
	}	
};

#endif // __Gizmo_h
