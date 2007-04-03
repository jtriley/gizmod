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

#include "GizmoEventPowermate.hpp"
#include "GizmoEventCPU.hpp"
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
	 * \brief  Faked constructor for the Python object
	 *
	 * Use this as the Object's constructor rather than __init__
	 * 
	 * This is to work around oddities that happen when constructing
	 * a Python object that uses a C++ class as its base
	 */
	virtual void			__construct__() = 0;
	
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
	 * \brief  Event triggers
	 */
	virtual void			onEvent(GizmoEventPowermate const * Event) = 0; ///< Powermate Event trigger
	virtual void			onEvent(GizmoEventCPU const * Event) = 0; ///< CPU Event trigger
	
	// construction / deconstruction
	GizmodEventHandlerInterface();
	virtual ~GizmodEventHandlerInterface();

private:
};

#endif // __GizmodEventHandlerInterface_h
