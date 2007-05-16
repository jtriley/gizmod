    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoClient.cpp
*** \brief GizmoClient class body
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

#include "GizmoClient.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <sstream>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoClient Default Constructor
 */
GizmoClient::GizmoClient() {
	mNoSendLEDEvents = true;
}

/**
 * \brief GizmoClient Destructor
 */
GizmoClient::~GizmoClient() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Send LIRC Event to server
 * \param  Event The Event
 * \param  Gizmo The Gizmo that is creating the event
 */
void GizmoClient::sendEventATIX10(GizmoEventATIX10 const & Event, GizmoATIX10 const & Gizmo) {
	// process the remote event
	if (!isClientConnected())
		return;
	
	// serialize
	stringstream OutStreamEvent;
	archive::text_oarchive OutArchiveEvent(OutStreamEvent);
	OutArchiveEvent << Event;
	
	stringstream OutStreamDevice;
	archive::text_oarchive OutArchiveDevice(OutStreamDevice);
	OutArchiveDevice << Gizmo;
		
	// might raise an exception, catch elsewhere!
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_ATIX10) + "|" + OutStreamEvent.str() + "|" + OutStreamDevice.str());
}

/**
 * \brief  Send CPUUsage Event to server
 * \param  Event The Event
 */
void GizmoClient::sendEventCPUUsage(GizmoEventCPUUsage const & Event) {
	// process the remote event
	if (!isClientConnected())
		return;
	
	// serialize
	stringstream OutStream;
	archive::text_oarchive OutArchive(OutStream);
	OutArchive << Event;
			
	// can raise exception
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_CPUUSAGE) + "|" + OutStream.str());
}

/**
 * \brief  Send LIRC Event to server
 * \param  Event The Event
 * \param  Gizmo The Gizmo that is creating the event
 */
void GizmoClient::sendEventLIRC(GizmoEventLIRC const & Event, GizmoLIRC const & Gizmo) {
	// process the remote event
	if (!isClientConnected())
		return;
	
	// serialize
	stringstream OutStreamEvent;
	archive::text_oarchive OutArchiveEvent(OutStreamEvent);
	OutArchiveEvent << Event;
	
	stringstream OutStreamDevice;
	archive::text_oarchive OutArchiveDevice(OutStreamDevice);
	OutArchiveDevice << Gizmo;
		
	// might raise an exception, catch elsewhere!
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_LIRC) + "|" + OutStreamEvent.str() + "|" + OutStreamDevice.str());
}

/**
 * \brief  Send LIRC Event to server
 * \param  Event The Event
 * \param  Gizmo The Gizmo that is creating the event
 */
void GizmoClient::sendEventPowermate(GizmoEventPowermate const & Event, GizmoPowermate const & Gizmo) {
	// process the remote event
	if (!isClientConnected())
		return;
	
	// serialize
	stringstream OutStreamEvent;
	archive::text_oarchive OutArchiveEvent(OutStreamEvent);
	OutArchiveEvent << Event;
	
	stringstream OutStreamDevice;
	archive::text_oarchive OutArchiveDevice(OutStreamDevice);
	OutArchiveDevice << Gizmo;
		
	// might raise an exception, catch elsewhere!
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_POWERMATE) + "|" + OutStreamEvent.str() + "|" + OutStreamDevice.str());
}

/**
 * \brief  Send Sound Visualization Event to server
 * \param  Event The Event
 */
void GizmoClient::sendEventSoundCard(GizmoEventSoundCard const & Event) {
	// process the remote event
	if (!isClientConnected())
		return;
		
	// serialize
	stringstream OutStream;
	archive::text_oarchive OutArchive(OutStream);
	OutArchive << Event;
			
	// can raise exception
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_SOUNDCARD) + "|" + OutStream.str());
}

/**
 * \brief  Send Sound Visualization Event to server
 * \param  Event The Event
 */
void GizmoClient::sendEventSoundVisualization(GizmoEventSoundVisualization const & Event) {
	// process the remote event
	if (!isClientConnected())
		return;
		
	// serialize
	stringstream OutStream;
	archive::text_oarchive OutArchive(OutStream);
	OutArchive << Event;
			
	// can raise exception
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_SOUNDVISUALIZATION) + "|" + OutStream.str());
}

/**
 * \brief  Send LIRC Event to server
 * \param  Event The Event
 * \param  Gizmo The Gizmo that is creating the event
 */
void GizmoClient::sendEventStandard(GizmoEventStandard const & Event, GizmoStandard const & Gizmo) {
	// process the remote event
	if ( (!isClientConnected()) || (Event.Type == GIZMO_EV_LED && mNoSendLEDEvents) )
		return;
	
	// serialize
	stringstream OutStreamEvent;
	archive::text_oarchive OutArchiveEvent(OutStreamEvent);
	OutArchiveEvent << Event;
	
	stringstream OutStreamDevice;
	archive::text_oarchive OutArchiveDevice(OutStreamDevice);
	OutArchiveDevice << Gizmo;
		
	// might raise an exception, catch elsewhere!
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_STANDARD) + "|" + OutStreamEvent.str() + "|" + OutStreamDevice.str());
}

/**
 * \brief  Send Sound Visualization Event to server
 * \param  Event The Event
 */
void GizmoClient::sendEventWindowFocus(GizmoEventWindowFocus const & Event) {
	// process the remote event
	if (!isClientConnected())
		return;
		
	// serialize
	stringstream OutStream;
	archive::text_oarchive OutArchive(OutStream);
	OutArchive << Event;
			
	// can raise exception
	sendToServer(lexical_cast<string>(GIZMO_EVENTCLASS_WINDOWFOCUS) + "|" + OutStream.str());
}
