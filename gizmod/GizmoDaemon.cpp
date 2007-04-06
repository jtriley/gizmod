    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoDaemon.cpp
*** \brief GizmoDaemon class body
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

#include "GizmoDaemon.hpp"
#include "GizmoEventPowermate.hpp"
#include "GizmoEventCPU.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/Util.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/filesystem/operations.hpp>

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace boost::python;
using namespace boost::filesystem;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs / defines
///////////////////////////////////////

/** 
 * \def   CONFIG_FILE
 * The default path of the config file
 */
#define CONFIG_FILE		PACKAGE_NAME ".conf"

/** 
 * \def   SCRIPT_DIR
 * The default path of the config file
 */
#define SCRIPT_DIR		PACKAGE_PREFIX "/share/gizmo/scripts/"

/** 
 * \def   SCRIPT_DISPATCH
 * The path of the initial config script
 */
#define SCRIPT_DISPATCH 	"Dispatch.py"

/** 
 * \def   SCRIPT_USER
 * The path of the user config script that gets run after SCRIPT_DISPATCH
 */
#define SCRIPT_USER		"User.py"

/** 
 * \def   EVENT_NODE_DIR
 * Default path to the event nodes
 */
#define EVENT_NODE_DIR		"/dev/input"

////////////////////////////////////////////////////////////////////////////
// C++ -> Python Exposures
///////////////////////////////////////

/**
 * \struct GizmodEventHandlerInterfaceWrap
 * \brief  Wrapper for GizmodEventHandlerInterface so Python can inherit the abstract class
 */
struct GizmodEventHandlerInterfaceWrap : public GizmodEventHandlerInterface {
	/// Default Constructor
	GizmodEventHandlerInterfaceWrap(PyObject * self_) : self(self_) {}

	void		__construct__()	 { return python::call_method<void>(self, "__construct__"); }
	bool		getInitialized() { return python::call_method<bool>(self, "getInitialized"); }
	void		initialize()	 { return python::call_method<void>(self, "initialize"); }
	void		onEvent(GizmoEventPowermate const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }
	void		onEvent(GizmoEventCPU const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }

	PyObject * 	self;		///< Pointer to self
};

/** 
 * \def   GIZMO_EVENT_PYTHON_DEFS
 * Macro for including the GizmoEvent base class functions in super classes
 */
#define GIZMO_EVENT_PYTHON_DEFS \
	.def("getEventType", &GizmoEvent::getEventType)

/**
 * \brief Python module definition
 */
BOOST_PYTHON_MODULE(GizmoDaemon) {
	/// GizmoDaemon Python Class Export
	class_<GizmoDaemon>("PyGizmoDaemon")
		.def("getVersion", & GizmoDaemon::getVersion)
		;
	
	/// GizmodEventHandlerInterface Python Class Export	
	class_<GizmodEventHandlerInterface, GizmodEventHandlerInterfaceWrap, boost::noncopyable>("GizmodEventHandler")
		;

	/// GizmoEventPowermate Python Class Export
	class_<GizmoEventPowermate>("GizmoEventPowermate")
		GIZMO_EVENT_PYTHON_DEFS
		;

	/// GizmoEventCPU Python Class Export
 	class_<GizmoEventCPU>("GizmoEventCPU")
		GIZMO_EVENT_PYTHON_DEFS
		;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
GizmoDaemon::GizmoDaemon() {
	cout << getProps();
	
	mConfigDir = SCRIPT_DIR;
	mEventsDir = EVENT_NODE_DIR;
	mInitialized = false;
	mpPyDispatcher = NULL;
}

/**
 * \brief Default Destructor
 */
GizmoDaemon::~GizmoDaemon() {
	cdbg << "GizmoDaemon Shutting Down..." << endl << endl;
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Enter the main run loop
 */
void GizmoDaemon::enterLoop() {
	if (!mInitialized)
		throw H::Exception("You must initialize GizmoDaemon first!", __FILE__, __FUNCTION__, __LINE__);
	
	watchForFileEvents();
}

/**
 * \brief Get the program's propers
 */
string GizmoDaemon::getProps() {
	return "\nGizmoDaemon v" + getVersion() + " -- (c) 2007, Tim Burrell <tim.burrell@gmail.com>\n";
}

/**
 * \brief Get the program's version information
 */
string GizmoDaemon::getVersion() {
	return string(PACKAGE_VERSION);
}

/**
 * \brief  Setup GizmoDaemon
 * 
 * Initialize GizmoDaemon
 */
void GizmoDaemon::initGizmod() {
	if (mInitialized)
		return;
	
	// initialize signals
	initSignals();
	
	// init python
	try {
		initPython();
	} catch (H::Exception & e) {
		throw e;
	} catch (exception & e) {
		throw H::Exception("Failed to Initialize Python!", __FILE__, __FUNCTION__, __LINE__);
	}

	// register all the devices
	try {
		registerDevices();
	} catch (H::Exception & e) {
		throw e;
	}
	
	mInitialized = true;
}

/**
 * \brief  Initialize the Python interpreter
 */
void GizmoDaemon::initPython() {
	try {
		cdbg1 << "Embedding Python Interpreter..." << endl;
		PyImport_AppendInittab("GizmoDaemon", &initGizmoDaemon);
		Py_Initialize();
		
		cdbg1 << "Initializing Python Environment..." << endl;
		object MainModule((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object MainNamespace = MainModule.attr("__dict__");
		
		// add Gizmo Daemon module automatically to the namespace
		object GizmoDaemonModule( (handle<>(PyImport_ImportModule("GizmoDaemon"))) );
		MainNamespace["GizmoDaemon"] = GizmoDaemonModule;
		
		// create a new object so the script can access this object
		scope(GizmoDaemonModule).attr("Gizmod") = ptr(this);
		
		// execute the main script code
		string ScriptFile = mConfigDir + SCRIPT_DISPATCH;
		cdbg << "Executing Dispatcher Python Script [" << ScriptFile << "]..." << endl;
		FILE * ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
		
		// Create the event dispatcher object so we can interact with it
		cdbg1 << "Creating Dispatcher Object" << endl;
		handle<> ignored((PyRun_String(
			"Dispatcher = GizmodDispatcher()\n",
			Py_file_input, MainNamespace.ptr(), MainNamespace.ptr())));
		
		// Grab the event dispatcher object so we can interact with it
		mpPyDispatcher = extract<GizmodEventHandlerInterface*>(MainNamespace["Dispatcher"]);
		
		// Initialize the dispatcher object
		mpPyDispatcher->__construct__();
		mpPyDispatcher->initialize();
		GizmoEventCPU e;
		mpPyDispatcher->onEvent(&e);
		cout << "Mod: " << e.getEventType() << endl;
			
		// execute the user script code
		ScriptFile = mConfigDir + SCRIPT_USER;
		cdbg << "Executing User Python Script [" << ScriptFile << "]..." << endl;
		ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
	} catch (error_already_set) {
		PyErr_Print();
		throw H::Exception("Failed to Execute Python Script!", __FILE__, __FUNCTION__, __LINE__);
	}
}

/**
 * \brief  generic Init stuff
 * \param  argc number of command line arguments
 * \param  argv command line arguments
 * \return true if the program should continue, false otherwise
 * 
 * load the config file, process command line options, etc
 */
bool GizmoDaemon::initialize(int argc, char ** argv) {
	// generic options
	options_description GenericOptions("Generic Options");
	GenericOptions.add_options()
		("debug,g",					"Enable debug mode")
		("help,h",					"Display informative help message")
		("verbosity,V",		value<int>(),		"Set debug vebosity level (0-5) [Default = 0]")
		("version,v",					"Print version information")
		;
				
	// config file options that can be loaded via command line as well
	options_description ConfigurationOptions("Configuration Options");
	ConfigurationOptions.add_options()
		("configdir,c",		value<string>(),	"Set config scripts directory") 
		("eventsdir,e",		value<string>(),	"Set event node directory (default: " EVENT_NODE_DIR ")")
		;
        
        // hiGizmoDaemonn options
	options_description HiddenOptions("Hidden Options");
	HiddenOptions.add_options();
       
        // create command line options group
        options_description CommandLineOptions;
        CommandLineOptions.add(GenericOptions).add(ConfigurationOptions).add(HiddenOptions);

        // create config file options group
        options_description ConfigFileOptions;
        ConfigFileOptions.add(ConfigurationOptions).add(HiddenOptions);
	
	// create a visible options group for help display
	options_description VisibleOptions("");
	VisibleOptions.add(GenericOptions).add(ConfigurationOptions);
	
	// create the variables map
	variables_map VarMap;
	
	// try parsing the command line
	try {
		store(parse_command_line(argc, argv, CommandLineOptions), VarMap);
	} catch (exception & e) {
		cout << VisibleOptions;
		throw H::Exception("Invalid Command Line Argument(s)");
	}

	// try parsing the config file
	try {
		ifstream ifs(CONFIG_FILE);
		store(parse_config_file(ifs, ConfigFileOptions), VarMap);
	} catch (exception & e) {
		cout << VisibleOptions;
		throw H::Exception("Invalid Configuration File");
	}
	
	// build the option map
	notify(VarMap);

	// check for options
	if (VarMap.count("help")) {
		cout << VisibleOptions << endl;
		return false;
	}
	if (VarMap.count("version")) {
		return false;
	}
	if (VarMap.count("debug")) {
		Debug::setDebugEnabled(true);	
		cdbg << "Debug Mode Enabled" << endl;
	}
	if (VarMap.count("verbosity")) {
		Debug::setDebugVerbosity(VarMap["verbosity"].as<int>());
		cdbg << "Debug Verbosity set to [" << VarMap["verbosity"].as<int>() << "]" << endl;
	}
	if (VarMap.count("configdir")) {
		mConfigDir = VarMap["configdir"].as<string>();
		if (mConfigDir[mConfigDir.length() - 1] != '/')
			mConfigDir += "/";
		cdbg << "Config Scripts Directory set to [" << VarMap["configdir"].as<string>() << "]" << endl;
	}
	if (VarMap.count("eventsdir")) {
		mEventsDir = VarMap["eventsdir"].as<string>();
		if (mEventsDir[mEventsDir.length() - 1] != '/')
			mEventsDir += "/";
		cdbg << "Event Node Directory set to [" << VarMap["eventsdir"].as<string>() << "]" << endl;
	}

	cout << endl;
	return true;
}

/**
 * \brief Event triggered when a new file is created
 * \param pWatchee The Watchee that triggered the event
 * \param FullPath The full (absolute) path of the new file
 * \param FileName The file name (relative ) of the new file
 */
void GizmoDaemon::onFileEventCreate(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName) {
	if (FileName.find("event") != 0) {
		cout << "onFileEventCreate [" << FullPath << "]" << endl;
		return;
	}
	addFileToWatch(FullPath, WATCH_INOUT);
}

/**
 * \brief Event triggered when a file is deleted
 * \param pWatchee The Watchee that triggered the event
 * \param FullPath The full (absolute) path of the new file
 * \param FileName The file name (relative ) of the new file
 */
void GizmoDaemon::onFileEventDelete(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName) {
	cout << "onFileEventDelete [" << FullPath << "]" << endl;
}

/**
 * \brief Event triggered when a file is disconnected
 * \param pWatchee The Watchee that triggered the event
 */
void GizmoDaemon::onFileEventDisconnect(boost::shared_ptr<H::FileWatchee> pWatchee) {
	cout << "onFileEventDisconnect [" << pWatchee->FileName << "]: " << pWatchee->DeviceName << endl;
}

/**
 * \brief Signal handler for SEGV
 */
void GizmoDaemon::onSignalSegv() {
	// override me
	cerr << "Segmentation Fault Detected" << endl;
	stopWatchingForFileEvents();
}

/**
 * \brief Signal handler for INT
 */
void GizmoDaemon::onSignalInt() {
	// override me
	cdbg << "Keyboard Interrupt Received..." << endl;
	stopWatchingForFileEvents();
}

/**
 * \brief Signal handler for HUP
 */
void GizmoDaemon::onSignalHup() {
	// override me
	cerr << "Unhandled HUP Signal" << endl;
}

/**
 * \brief Signal handler for QUIT
 */
void GizmoDaemon::onSignalQuit() {
	// override me
	cdbg << "Request to Quit Received..." << endl;
	stopWatchingForFileEvents();
}

/**
 * \brief Signal handler for KILL
 */
void GizmoDaemon::onSignalKill() {
	// override me
	cdbg << "Kill signal Received..." << endl;
	stopWatchingForFileEvents();
}

/**
 * \brief Signal handler for TERM
 */
void GizmoDaemon::onSignalTerm() {
	// override me
	cdbg << "Request to Terminate Received..." << endl;
	stopWatchingForFileEvents();
}

/**
 * \brief Signal handler for STOP
 */
void GizmoDaemon::onSignalStop() {
	// override me
	cdbg << "Request to Stop Received..." << endl;
	stopWatchingForFileEvents();
}

/**
 * \brief Signal handler for Unknown Signals
 */
void GizmoDaemon::onSignalUnknown(int Signal) {
	// override me
	cerr << "Unhandled Unknown Signal" << endl;
}

/**
 * \brief  Register all the system devices with Gizmo Daemon
 * 
 * This function creates a registry of all the attached devices
 * and inserts them into Python for use by the user
 */
void GizmoDaemon::registerDevices() {
	cdbg << "Registering Devices..." << endl;
	
	// register input event devices
	registerInputEventDevices();
	
	// register CPU usage device
}

/**
 * \brief  Register all of the input event devices with Gizmo Daemon
 */
void GizmoDaemon::registerInputEventDevices() {
	cdbg << "Registering Input Event Devices in [" << mEventsDir << "]" << endl;
	path EventsDirPath(mEventsDir);
	if (!filesystem::exists(EventsDirPath))
		throw H::Exception("Input Event dir [" + mEventsDir + "] does NOT exist or permissions are wrong!", __FILE__, __FUNCTION__, __LINE__);
	
	// register the directory itself
	addFileToWatch(mEventsDir, WATCH_INOUT);
	
	// now register the event nodes
	// get a file listing
	std::vector<string> eventsFiles;
	directory_iterator endItr;
	for (directory_iterator iter(mEventsDir); iter != endItr; iter ++) {
		if ( (!filesystem::is_directory(*iter)) && (!filesystem::symbolic_link_exists(*iter)) ) {
			if (iter->leaf().find("event") != 0)
				continue;
			eventsFiles.push_back(mEventsDir + "/" + iter->leaf());
		}
	}
	
	// sort the list of input event nodes
	sort_all(eventsFiles);
	apply_func_args(eventsFiles, &FileEventWatcher::addFileToWatch, this, WATCH_INOUT);
}
