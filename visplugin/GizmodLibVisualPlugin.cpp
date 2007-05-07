    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodLibVisualPlugin.cpp
*** \brief GizmodLibVisualPlugin class body
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

#include "GizmodLibVisualPlugin.hpp"
#include "../libGizmod/GizmoEventSoundVisualization.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/SocketException.hpp"

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmodLibVisualPlugin Default Constructor
 */
GizmodLibVisualPlugin::GizmodLibVisualPlugin() {
	mServerHost = "localhost";
	mServerPort = 30303;
	Debug::setDebugEnabled(true);
	Debug::setDebugLog("/tmp/actor_gizmod.log");
}

/**
 * \brief GizmodLibVisualPlugin Destructor
 */
GizmodLibVisualPlugin::~GizmodLibVisualPlugin() {
	closeSocket();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Initialize the plugin
 */
void GizmodLibVisualPlugin::init() {
	cdbg << "Init" << endl;
	
	// initialize the client
	try {
		cdbg << "Connecting to [" << mServerHost << "] at Port [" << mServerPort << "]..." << endl;
		connectToServer(mServerHost, mServerPort);
		cdbg << "Connected to [" << mServerHost << "] at Port [" << mServerPort << "]..." << endl;
		GizmoEventSoundVisualization Event(SOUNDVISUALIZATION_CONNECT);
		sendEventSoundVisualization(Event);
	} catch (SocketException const & e) {
		cdbg << e.getExceptionMessage() << endl;
	}
}

/**
 * \brief  Shutdown the plugin
 */
void GizmodLibVisualPlugin::shutdown() {
	GizmoEventSoundVisualization Event(SOUNDVISUALIZATION_DISCONNECT);
	sendEventSoundVisualization(Event);
	cdbg << "Shutdown" << endl;
}

/**
 * \brief  Render the sound data
 * \param  PCMData The sound data
 */
void GizmodLibVisualPlugin::render(float VULeft, float VURight, float VUCombined) {
	GizmoEventSoundVisualization Event(VULeft, VURight, VUCombined);
	sendEventSoundVisualization(Event);
}
