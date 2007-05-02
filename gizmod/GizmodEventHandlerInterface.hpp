    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodEventHandlerInterface.hpp
*** \brief GizmodEventHandlerInterface class header file
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

#ifndef __GizmodEventHandlerInterface_h
#define __GizmodEventHandlerInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEventATIX10.hpp"
#include "GizmoEventCPU.hpp"
#include "GizmoEventLIRC.hpp"
#include "GizmoEventPowermate.hpp"
#include "GizmoEventSoundCard.hpp"
#include "GizmoEventStandard.hpp"
#include "GizmoEventWindowFocus.hpp"
#include "Gizmo.hpp"
#include "GizmoATIX10.hpp"
#include "GizmoCPU.hpp"
#include "GizmoLIRC.hpp"
#include "GizmoPowermate.hpp"
#include "GizmoStandard.hpp"
#include "../libH/FileEventWatcher.hpp"
#include <string>
#include <boost/python.hpp>

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmodEventHandlerInterface
 * \brief Main GizmodEventHandlerInterface class
 */
class GizmodEventHandlerInterface : public boost::noncopyable {
public:
	/**
	 * \brief  Get whether or not the object has been initialized
	 * \return (bool) True if initialized
	 */
	virtual bool			getInitialized() = 0;
	
	/**
	 * \brief  Script initialization code 
	 *
	 * This python function gets called by GizmoDeamon and is intended to allow for
	 * user specific initialization code to be executed during program startup.
	 * 
	 * It is defined in Gizmod.py in class GizmodDispatcher that inherits from GizmodEventHandler
	 */
	virtual void			initialize() = 0; 		///< Initialization that gets called inside python to init python stuff
			
	/**
	 * \brief  Event triggered when device has been deregistered
	 * \param  Device The device
	 */
	virtual void			onDeregisterDevice(GizmoATIX10 const * Device) = 0;	
	
	/**
	 * \brief  Event triggered when device has been deregistered
	 * \param  Device The device
	 */
	virtual void			onDeregisterDevice(GizmoCPU const * Device) = 0;
	
	/**
	 * \brief  Event triggered when device has been deregistered
	 * \param  Device The device
	 */
	virtual void			onDeregisterDevice(GizmoLIRC const * Device) = 0;
	
	/**
	 * \brief  Event triggered when device has been deregistered
	 * \param  Device The device
	 */
	virtual void			onDeregisterDevice(GizmoPowermate const * Device) = 0;
			
	/**
	 * \brief  Event triggered when device has been deregistered
	 * \param  Device The device
	 */
	virtual void			onDeregisterDevice(GizmoStandard const * Device) = 0;	
	
	/**
	 * \brief  ATI X10 Event trigger
	 * \param  Event The event information 
	 * \param  Device The device that triggered the event
	 */
	virtual void			onEvent(GizmoEventATIX10 const * Event, GizmoATIX10 const * Device) = 0;
	
	/**
	 * \brief  CPU Event trigger
	 * \param  Event The event information 
	 * \param  Device The device that triggered the event
	 */
	virtual void			onEvent(GizmoEventCPU const * Event, GizmoCPU const * Device) = 0;
	
	/**
	 * \brief  LIRC Event trigger
	 * \param  Event The event information 
	 * \param  Device The device that triggered the event
	 */
	virtual void			onEvent(GizmoEventLIRC const * Event, GizmoLIRC const * Device) = 0;
	
	/**
	 * \brief  Powermate Event trigger
	 * \param  Event The event information 
	 * \param  Device The device that triggered the event
	 */
	virtual void			onEvent(GizmoEventPowermate const * Event, GizmoPowermate const * Device) = 0;
		
	/**
	 * \brief  SoundCard Event trigger
	 * \param  Event The event information 
	 */
	virtual void			onEvent(GizmoEventSoundCard const * Event) = 0;
	
	/**
	 * \brief  Standard Event trigger
	 * \param  Event The event information 
	 * \param  Device The device that triggered the event
	 */
	virtual void			onEvent(GizmoEventStandard const * Event, GizmoStandard const * Device) = 0;
	
	/**
	 * \brief  Window Focus Event trigger
	 * \param  Event The event information 
	 */
	virtual void			onEvent(GizmoEventWindowFocus const * Event) = 0;
	
	/**
	 * \brief  Event triggered when a new device is being registered
	 * \param  DeviceInformation The information about the device being registered
	 * \return The class of the device
	 */
	virtual GizmoClass		onQueryDeviceClass(H::DeviceInfo const DeviceInformation) = 0;
	
	/**
	 * \brief  Event triggered when a new device has been registered
	 * \param  Device The device
	 */
	virtual void			onRegisterDevice(GizmoATIX10 const * Device) = 0;
	
	/**
	 * \brief  Event triggered when a new device has been registered
	 * \param  Device The device
	 */
	virtual void			onRegisterDevice(GizmoCPU const * Device) = 0;
	
	/**
	 * \brief  Event triggered when a new device has been registered
	 * \param  Device The device
	 */
	virtual void			onRegisterDevice(GizmoLIRC const * Device) = 0;
	
	/**
	 * \brief  Event triggered when a new device has been registered
	 * \param  Device The device
	 */
	virtual void			onRegisterDevice(GizmoPowermate const * Device) = 0;
		
	/**
	 * \brief  Event triggered when a new device has been registered
	 * \param  Device The device
	 */
	virtual void			onRegisterDevice(GizmoStandard const * Device) = 0;	
		
	// construction / deconstruction
	GizmodEventHandlerInterface();
	virtual ~GizmodEventHandlerInterface();

private:
};

#endif // __GizmodEventHandlerInterface_h
