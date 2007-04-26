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
#include "X11FocusWatcher.hpp"
#include "../libH/FileEventWatcher.hpp"
#include "../libH/SignalHandler.hpp"
#include <string>
#include <ext/hash_map>
#include <map>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

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
class GizmoDaemon : public H::FileEventWatcher, H::SignalHandler, X11FocusWatcher {
public:
	// public functions
	void				enterLoop();		///< Enter the main run loop
	X11FocusEvent 	 		getCurrentFocus();	///< Get currently focused window
	bool				getDebugEnabled();	///< Is debug mode enabled?
	GizmodEventHandlerInterface *	getDispatcher();	///< Get the event handler / dispatcher
	boost::shared_ptr<Gizmo>	getGizmoByFileName(std::string FileName); ///< Get a Gizmo by its file name
	std::string			getVersion();		///< Get version string
	void				initGizmod();		///< Initialize GizmoDaemon Evolution
	bool				initialize(int argc, char ** argv); ///< generic init stuff, command line, etc
	virtual void			onFileEventCreate(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a new file is created
	virtual void			onFileEventDelete(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a file is deleted
	virtual void			onFileEventDisconnect(boost::shared_ptr<H::FileWatchee> pWatchee); ///< Event triggered when a device is disconnected
	virtual void			onFileEventRead(boost::shared_ptr<H::FileWatchee> pWatchee, DynamicBuffer<char> const & ReadBuffer); ///< Event triggered when data is waiting on a device
	virtual void			onFileEventRegister(boost::shared_ptr<H::FileWatchee> pWatchee); ///< Event triggered when a new device is registered
	virtual void			onFocusIn(X11FocusEvent const & Event); ///< Event triggered on a Focus In
	virtual void			onFocusOut(X11FocusEvent const & Event); ///< Event triggered on a Focus Out
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
	std::string			getUserScriptDirPaths();///< Get all of the dirs inside the user script dir
	void				initPython();		///< Initialize Python
	void 				loadUserScripts();	///< Load user scripts
	void 				loadUserScriptsFunctor(std::string UserScript); ///< Load user scripts functor
	void 				registerDevices();	///< Register all the attached system devices
	void				registerInputEventDevices(); ///< Register input event devices (/dev/input/*)
	void 				registerLircDevice();	///< Register the LIRC device
	
	// private member vars
	std::string			mConfigDir;		///< Configuration scripts directory
	X11FocusEvent			mCurrentFocus;		///< Currently focused window
	std::string			mEventsDir;		///< Event node directory
	std::map< std::string, boost::shared_ptr<Gizmo> > mGizmos; ///< Map of Gizmos
	bool				mInitialized;		///< Has GizmoDaemon been properly initialized?
	std::string			mLircDev;		///< Lirc device node
	GizmodEventHandlerInterface * 	mpPyDispatcher;		///< The GizmoDaemonDispatcher Python object
	boost::python::object		mPyMainModule;		///< The Python Main Module
	boost::python::object		mPyMainNamespace;	///< The Python Main Namespace
	
	// static private member vars
	static boost::mutex		mMutexScript;		///< Mutex for the python script
};

#endif // __GizmoDaemon_h
