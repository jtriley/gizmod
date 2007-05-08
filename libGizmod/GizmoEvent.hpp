    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEvent.hpp
*** \brief GizmoEvent class header
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

#ifndef __GizmoEvent_h
#define __GizmoEvent_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "../libH/DynamicBuffer.hpp"
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

/**
 * \enum  GizmoEventClass
 * \brief These values tell GizmoDaemon what classes to use to represent the devices during events
 *
 * These values are repsented in Python by the same extension, under the enum class GizmoEventClass
 * For example: GizmoEventClass.Standard, and GizmoEventClass.Powermate
 *
 * GIZMO_EVENTCLASS_ATIX10 is used with ATI X10 RF Remotes
 * GIZMO_EVENTCLASS_CPUUSAGE is used for CPU Usage events
 * GIZMO_EVENTCLASS_LIRC is used with LIRC (Infrared) devices (such as remote controls)
 * GIZMO_EVENTCLASS_POWERMATE is the class used for Griffin PowerMate, and SoundKnob devices
 * GIZMO_EVENTCLASS_SOUNDCARD is used for sound card event
 * GIZMO_EVENTCLASS_SOUNDVISUALIZATION is used for sound visualization events
 * GIZMO_EVENTCLASS_STANDARD is the default class and is used for all devices except ones with
 * 	special handlers
 * GIZMO_EVENTCLASS_WINDOWFOCUS is triggered when a Window Focus event happens
 */
typedef enum {
	GIZMO_EVENTCLASS_ATIX10,
	GIZMO_EVENTCLASS_CPUUSAGE,
	GIZMO_EVENTCLASS_LIRC,
	GIZMO_EVENTCLASS_POWERMATE,
	GIZMO_EVENTCLASS_SOUNDCARD,
	GIZMO_EVENTCLASS_SOUNDVISUALIZATION,
	GIZMO_EVENTCLASS_STANDARD,
	GIZMO_EVENTCLASS_WINDOWFOCUS,
} GizmoEventClass;

/**
 * \def    GIZMO_EVENTCLASS_MAX
 * \brief  Max event class value
 */
#define GIZMO_EVENTCLASS_MAX	GIZMO_EVENTCLASS_WINDOWFOCUS
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEvent
 * \brief Base class of all GizmoEvents
 *
 * This class is the base of all GizmoEvents attached to the system.
 * Each gizmo must inherit this class
 */
class GizmoEvent {
public:
	// public functions
	GizmoEventClass			getClass();			///< Get the class of the Gizmo
	
	// construction / deconstruction
	GizmoEvent();							///< Serialize Constructor
	GizmoEvent(GizmoEventClass Class);				///< Default Constructor
	virtual ~GizmoEvent();						///< Destructor
	
protected:
	// protected member variables
	GizmoEventClass			mClass;				///< Class of the Gizmo
	
private:
	// private functions
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & mClass;
	}
};

#endif // __GizmoEvent_h
