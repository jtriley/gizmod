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
#include "GizmoUtils.hpp"
#include "../libGizmod/Alsa.hpp"
#include "../libGizmod/CPUUsage.hpp"
#include "../libGizmod/Gizmo.hpp"
#include "../libGizmod/GizmoClient.hpp"
#include "../libGizmod/Processes.hpp"
#include "../libGizmod/X11FocusWatcher.hpp"
#include "../libH/FileEventWatcher.hpp"
#include "../libH/SignalHandler.hpp"
#include "../libH/SocketServer.hpp"
#include <ext/hash_map>
#include <map>
#include <string>
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
class GizmoDaemon : 
	public H::FileEventWatcher, 
	private H::SignalHandler, 
	public X11FocusWatcher,
	public Alsa,
	public Processes,
	public CPUUsage,
	public SocketServer,
	public GizmoClient,
	public GizmoUtils
{
public:
	// public functions
	bool				checkVersion(double Version, bool Strict); ///< See if a version matches ours
	void				enterLoop();			///< Enter the main run loop
	X11FocusEvent 	 		getCurrentFocus();		///< Get currently focused window
	bool				getDebugEnabled();		///< Is debug mode enabled?
	GizmodEventHandlerInterface *	getDispatcher();		///< Get the event handler / dispatcher
	boost::shared_ptr<Gizmo>	getGizmoByFileName(std::string FileName); ///< Get a Gizmo by its file name
	int 				getNumGizmosByClass(GizmoClass Class); ///< Get number of Gizmos of a particular class
	bool				getReloadConfig();		///< Get whether or not to reload the config file
	bool				getUseKeyboardLEDs();		///< Get whether or not to visualize on the Keyboard LEDs
	bool				getUseRemoteControl();		///< Get whether or not to allow remote control
	double				getVersion();			///< Get version string
	void				initGizmod();			///< Initialize GizmoDaemon Evolution
	bool				initialize(int argc, char ** argv); ///< generic init stuff, command line, etc
	void 				printNiceScriptInit(int Width, std::string Text1, std::string Text2, std::string Text3); ///< Print a nice looking init string
	void				signalShutdown();		///< Shutdown gizmod
		
	// construction / deconstruction
	GizmoDaemon();							///< Default Constructor
	virtual ~GizmoDaemon();						///< Destructor

private:
	// private functions
	void 				deleteGizmo(std::string FileName); ///< Delete a Gizmo
	void				deserializeMessage(GizmoEventClass EventClass, std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageATIX10(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageCPUUsage(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageLIRC(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessagePowermate(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageSoundcard(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageSoundVisualization(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageStandard(std::string const & Message); ///< Deserialize a network message into event Objects
	void				deserializeMessageWindowFocus(std::string const & Message); ///< Deserialize a network message into event Objects
	int 				getGizmoClassID(GizmoClass Class); ///< Get number of Gizmos of a particular class
	std::string	 		getProps();			///< Get version information
	std::string			getUserScriptDirPaths();	///< Get all of the dirs inside the user script dir
	void 				handleFileEventReadATIX10(GizmoATIX10 & pGizmo, DynamicBuffer<char> const & ReadBuffer); ///< Handle incoming ATIX10 events
	void 				handleFileEventReadLIRC(GizmoLIRC & pGizmo, DynamicBuffer<char> const & ReadBuffer); ///< Handle incoming LIRC events
	void 				handleFileEventReadPowermate(GizmoPowermate & pGizmo, DynamicBuffer<char> const & ReadBuffer); ///< Handle incoming Powermate events
	void 				handleFileEventReadStandard(GizmoStandard & pGizmo, DynamicBuffer<char> const & ReadBuffer); ///< Handle incoming Standard events
	void				initPython();			///< Initialize Python
	void 				loadUserScripts();		///< Load user scripts
	void 				loadUserScriptsFunctor(std::string UserScript); ///< Load user scripts functor
	virtual void			onAlsaEventMixerElementAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer); ///< Triggered when a mixer element is discovered
	virtual void			onAlsaEventMixerElementChange(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer); ///< Triggered when a mixer element is discovered
	virtual void			onAlsaEventMixerElementDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer); ///< Triggered when a mixer element is detached
	virtual void			onAlsaEventSoundCardAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard); ///< Triggered when a new sound card is detected
	virtual void			onAlsaEventSoundCardDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard); ///< Triggered when a sound card is removed
	virtual void			onCPUUsage(std::vector< boost::shared_ptr<CPUUsageInfo> > const & Event); ///< Event triggered when CPU Usage stats are updated
	virtual void			onFileEventCreate(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a new file is created
	virtual void			onFileEventDelete(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName); ///< Event triggered when a file is deleted
	virtual void			onFileEventDisconnect(boost::shared_ptr<H::FileWatchee> pWatchee); ///< Event triggered when a device is disconnected
	virtual void			onFileEventRead(boost::shared_ptr<H::FileWatchee> pWatchee, DynamicBuffer<char> const & ReadBuffer); ///< Event triggered when data is waiting on a device
	virtual void			onFileEventRegister(boost::shared_ptr<H::FileWatchee> pWatchee); ///< Event triggered when a new device is registered
	virtual void			onFileEventWatchBegin();	///< Event called when the class will begin watching for events (and blocking)
	virtual void			onFileEventWatchEnd();		///< Event called when the class has ended watching for events (and done blocking)
	virtual void			onFocusIn(X11FocusEvent const & Event); ///< Event triggered on a Focus In
	virtual void			onFocusOut(X11FocusEvent const & Event); ///< Event triggered on a Focus Out
	virtual void			onSignalSegv();			///< Signal handler for SEGV
	virtual void			onSignalInt();			///< Signal handler for INT
	virtual void			onSignalHup();			///< Signal handler for HUP
	virtual void			onSignalQuit();			///< Signal handler for QUIT
	virtual void			onSignalKill();			///< Signal handler for KILL
	virtual void			onSignalTerm();			///< Signal handler for TERM
	virtual void			onSignalStop();			///< Signal handler for STOP
	virtual void			onSignalUnknown(int Signal); ///< Signal handler for Unknown Signals
	virtual void			onSocketClientConnect(Socket const & socket); ///< Handle a socket connection
	virtual void 			onSocketClientDisconnect(Socket const & socket); ///< Handle a socket read
	virtual void 			onSocketClientMessage(Socket const & socket, std::string const & Message); ///< Event triggered on a socket message
	virtual void			onSocketClientRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer); ///< Handle a socket read
	virtual void			onSocketServerConnect(boost::shared_ptr<Socket> pSocket); ///< Event triggered when a new connection is detected
	virtual void 			onSocketServerDisconnect(Socket const & socket); ///< Event triggered on a socket disconnect
	virtual void 			onSocketServerMessage(Socket const & socket, std::string const & Message); ///< Event triggered on a socket message
	virtual void 			onSocketServerRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer); ///< Event triggered on a socket read
	void 				registerDevices();		///< Register all the attached system devices
	void				registerInputEventDevices();	///< Register input event devices (/dev/input/*)
	void 				registerLircDevice();		///< Register the LIRC device
	void				setConfigDir();			///< Set the config dir
	void				setVersionInfo();		///< Set the version information
	
	// private member vars
	std::string			mClientHost;			///< Remote host to forward events to 
	int				mClientPort;			///< Port to forward events to
	std::string			mConfigDir;			///< Configuration scripts directory
	X11FocusEvent			mCurrentFocus;			///< Currently focused window
	bool				mDisabledALSA;			///< Disable ALSA support
	bool				mDisabledCPUUsage;		///< Disable CPU Usage reporting
	bool				mDisabledX11;			///< Disable X11 support
	bool				mDisableShutdownMessage;	///< Disable the shutdown message / animation
	std::string			mEventsDir;			///< Event node directory
	std::map< std::string, boost::shared_ptr<Gizmo> > mGizmos; 	///< Map of Gizmos
	bool				mInitialized;			///< Has GizmoDaemon been properly initialized?
	std::string			mLircDev;			///< Lirc device node
	bool				mLocalDisabled;			///< Disable local processing of events?
	GizmodEventHandlerInterface * 	mpPyDispatcher;			///< The GizmoDaemonDispatcher Python object
	boost::python::object		mPyMainModule;			///< The Python Main Module
	boost::python::object		mPyMainNamespace;		///< The Python Main Namespace
	bool				mReloadConfig;			///< Reload the config rather than exit?
	bool				mServerEnabled;			///< Allow incoming connections
	int				mServerPort;			///< Port of the server
	bool				mShuttingDown;			///< Shutting down?
	bool				mUseKeyboardLEDs;		///< Allow Gizmod to visualize on the Keyboard LEDs
	bool				mUseRemoteControl;		///< Allow remote translation of events into local events
	double				mVersion;			///< Version
	int				mVersionMajor;			///< Version majorus
	int				mVersionMinor;			///< Version minorus
	
	// static private member vars
	static boost::mutex		mMutexScript;			///< Mutex for the python script
};

#endif // __GizmoDaemon_h
