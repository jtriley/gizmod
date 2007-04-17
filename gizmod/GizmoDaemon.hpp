    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoDaemon.hpp
*** \brief GizmoDaemon class header file
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

#ifndef __GizmoDaemon_h
#define __GizmoDaemon_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmodEventHandlerInterface.hpp"
#include "Gizmo.hpp"
#include "../libH/FileEventWatcher.hpp"
#include "../libH/SignalHandler.hpp"
#include <string>
#include <ext/hash_map>
#include <map>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////////////////
// Typedef's Enums
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoDaemon
 * \brief Main GizmoDaemon class
 * \todo  Replace for loops (in onFileEventRead) with boost::foreach when the new version comes out!
 */
class GizmoDaemon : public H::FileEventWatcher, H::SignalHandler {
public:
	// public functions
	void				enterLoop();		///< Enter the main run loop
	boost::shared_ptr<Gizmo>	getGizmoByFileName(std::string FileName); ///< Get a Gizmo by its file name
	std::string			getVersion();		///< Get version string
	void				initGizmod();		///< Initialize GizmoDaemon Evolution
	bool				initialize(int argc, char ** argv); ///< generic init stuff, command line, etc
	virtual void			onFileEventCreate(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a new file is created
	virtual void			onFileEventDelete(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a file is deleted
	virtual void			onFileEventDisconnect(boost::shared_ptr<H::FileWatchee> pWatchee); ///< Event triggered when a device is disconnected
	virtual void			onFileEventRead(boost::shared_ptr<H::FileWatchee> pWatchee, DynamicBuffer<char> const & ReadBuffer); ///< Event triggered when data is waiting on a device
	virtual void			onFileEventRegister(boost::shared_ptr<H::FileWatchee> pWatchee); ///< Event triggered when a new device is registered
	virtual void			onSignalSegv();		///< Signal handler for SEGV
	virtual void			onSignalInt();		///< Signal handler for INT
	virtual void			onSignalHup();		///< Signal handler for HUP
	virtual void			onSignalQuit();		///< Signal handler for QUIT
	virtual void			onSignalKill();		///< Signal handler for KILL
	virtual void			onSignalTerm();		///< Signal handler for TERM
	virtual void			onSignalStop();		///< Signal handler for STOP
	virtual void			onSignalUnknown(int Signal); ///< Signal handler for Unknown Signals
		
	// construction / deconstruction
	GizmoDaemon();						///< Default Constructor
	virtual ~GizmoDaemon();					///< Destructor

private:
	// private functions
	void 				deleteGizmo(std::string FileName); ///< Delete a Gizmo
	std::string	 		getProps();		///< Get version information
	void				initPython();		///< Initialize Python
	void 				registerDevices();	///< Register all the attached system devices
	void				registerInputEventDevices(); ///< Register input event devices (/dev/input/*)
	
	// private member vars
	std::string			mConfigDir;		///< Configuration scripts directory
	std::string			mEventsDir;		///< Event node directory
	bool				mInitialized;		///< Has GizmoDaemon been properly initialized?
	GizmodEventHandlerInterface * 	mpPyDispatcher;		///< The GizmoDaemonDispatcher Python object
	std::map< std::string, boost::shared_ptr<Gizmo> > mGizmos; ///< Map of Gizmos
};

#endif // __GizmoDaemon_h
