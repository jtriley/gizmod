    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoClient.hpp
*** \brief GizmoClient class header
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

#ifndef __GizmoClient_h
#define __GizmoClient_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoATIX10.hpp"
#include "GizmoLIRC.hpp"
#include "GizmoPowermate.hpp"
#include "GizmoStandard.hpp"
#include "GizmoEventATIX10.hpp"
#include "GizmoEventCPUUsage.hpp"
#include "GizmoEventLIRC.hpp"
#include "GizmoEventPowermate.hpp"
#include "GizmoEventSoundCard.hpp"
#include "GizmoEventSoundVisualization.hpp"
#include "GizmoEventStandard.hpp"
#include "GizmoEventWindowFocus.hpp"
#include "../libH/SocketClient.hpp"

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoClient
 * \brief This class can be used to make a connection to the server
 *
 * All you need to do is call SocketClient::connectToServer!
 * Then you're a client, and can use the rest of this class
 */
class GizmoClient : public H::SocketClient {
public:
	// public functions
	void				sendEventATIX10(GizmoEventATIX10 const & Event, GizmoATIX10 const & Gizmo); ///< Send ATIX10 Event to server
	void				sendEventCPUUsage(GizmoEventCPUUsage const & Event); ///< Send CPUUsage Event to server
	void				sendEventLIRC(GizmoEventLIRC const & Event, GizmoLIRC const & Gizmo); ///< Send LIRC Event to server
	void				sendEventPowermate(GizmoEventPowermate const & Event, GizmoPowermate const & Gizmo); ///< Send Powermate Event to server
	void				sendEventSoundCard(GizmoEventSoundCard const & Event); ///< Send Sound Card Event to server
	void				sendEventSoundVisualization(GizmoEventSoundVisualization const & Event); ///< Send Sound Visualization Event to server
	void				sendEventStandard(GizmoEventStandard const & Event, GizmoStandard const & Gizmo); ///< Send Powermate Event to server
	void				sendEventWindowFocus(GizmoEventWindowFocus const & Event); ///< Send Window Focus Event to server
	
	// construction / deconstruction
	GizmoClient();							///< Default Constructor
	virtual ~GizmoClient();						///< Destructor
	
private:
	// private functions
	
	// private member variables
};

#endif // __GizmoClient_h
