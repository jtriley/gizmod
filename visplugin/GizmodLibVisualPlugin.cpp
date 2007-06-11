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
#include "../libH/UtilFile.hpp"
#include <fstream>

using namespace std;
using namespace H;
using namespace Gizmod;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def    DEFAULT_HOST
 * \brief  Default host to connect to
 */
#define DEFAULT_HOST	"localhost"

/**
 * \def    DEFAULT_PORT
 * \brief  Default port to connect to
 */
#define DEFAULT_PORT	30303

/**
 * \def    CONFIG_FILE
 * \brief  Path of the config file
 */
#define CONFIG_FILE	"~/.gizmod/libVisualPlugin.config"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmodLibVisualPlugin Default Constructor
 */
GizmodLibVisualPlugin::GizmodLibVisualPlugin() {
	mServerHost = DEFAULT_HOST;
	mServerPort = DEFAULT_PORT;
	//Debug::setDebugEnabled(true);
	//Debug::setDebugLog("/tmp/actor_gizmod.log");
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
	readConfig();
	
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
 * \brief  Read the config file
 */
void GizmodLibVisualPlugin::readConfig() {
	string ConfigFile = CONFIG_FILE;
	UtilFile::relativeToAbsolute(ConfigFile);
	cdbg << "Read Config [" << ConfigFile << "]" << endl;
	ifstream ifs(ConfigFile.c_str());
	if (!ifs.is_open()) {
		writeConfig();
		return;
	}
	
	string Line;
	while (getline(ifs, Line)) {
		size_t eqPos = Line.find("=");
		if (eqPos == string::npos)
			continue;
		string Var = Line.substr(0, eqPos);
		string Val = Line.substr(eqPos + 1);
		
		if (Var == "host")
			mServerHost = Val;
		else if (Var == "port")
			mServerPort = atoi(Val.c_str());
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
 * \param  VULeft VU information for the left channel
 * \param  VURight VU information for the right channel
 * \param  VUCombined VU information for both channels
 */
void GizmodLibVisualPlugin::render(float VULeft, float VURight, float VUCombined) {
	GizmoEventSoundVisualization Event(VULeft, VURight, VUCombined);
	sendEventSoundVisualization(Event);
}

/**
 * \brief  Write a config file
 */
void GizmodLibVisualPlugin::writeConfig() {
	string ConfigFile = CONFIG_FILE;
	UtilFile::relativeToAbsolute(ConfigFile);
	cdbg << "Write Config [" << ConfigFile << "]" << endl;
	UtilFile::touchRecursive(ConfigFile);
	ofstream ofs(ConfigFile.c_str());
	if (!ofs.is_open())
		return;
	ofs << "host=" << DEFAULT_HOST << endl;
	ofs << "port=" << DEFAULT_PORT << endl;
}
