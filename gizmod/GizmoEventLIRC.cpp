    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventLIRC.cpp
*** \brief GizmoEventLIRC class body
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

#include "GizmoEventLIRC.hpp"
#include "GizmoLinuxInputDevice.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/Util.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <bitset>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def   GIZMO_EVENT_LIRC_TYPE
 * \brief String type of this event
 */
#define GIZMO_EVENT_LIRC_TYPE	"LIRC"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoEventLIRC Default Constructor
 */
GizmoEventLIRC::GizmoEventLIRC() : GizmoEvent(GIZMO_EVENTCLASS_LIRC) {
}

/**
 * \brief GizmoEventLIRC Init Constructor
 */
GizmoEventLIRC::GizmoEventLIRC(std::string const & InputEvent) : GizmoEvent(GIZMO_EVENTCLASS_LIRC) {
	LIRCData = InputEvent;
	
	// create the bitstring	
	for (size_t lp = 0; lp < LIRCData.length(); lp++) {
		bitset<8> bits(LIRCData[lp]);
		LIRCDataBitString += bits.to_string();
	}
}

/**
 * \brief GizmoEventLIRC Destructor
 */
GizmoEventLIRC::~GizmoEventLIRC() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Build an event vector from a read buffer
 * \param  EventVector Reference to a vector which will contain the results
 * \param  Buffer The bufer to convert into events
 */
void GizmoEventLIRC::buildEventsVectorFromBuffer(std::vector< boost::shared_ptr<GizmoEventLIRC> > & EventVector, H::DynamicBuffer<char> const & Buffer) {
	string LIRCData(Buffer.getBuffer(), Buffer.length());
	EventVector.push_back(boost::shared_ptr<GizmoEventLIRC>(new GizmoEventLIRC(LIRCData)));
}

/**
 * \brief  Get the type of this Gizmo
 * \return Type of the Gizmo
 */
std::string GizmoEventLIRC::getEventType() {
	return GIZMO_EVENT_LIRC_TYPE;
}
