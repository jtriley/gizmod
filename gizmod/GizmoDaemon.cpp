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
#include "GizmoEventCPU.hpp"
#include "GizmoEventLIRC.hpp"
#include "GizmoEventPowermate.hpp"
#include "GizmoEventSoundCard.hpp"
#include "GizmoEventStandard.hpp"
#include "GizmoEventWindowFocus.hpp"
#include "GizmoCPU.hpp"
#include "GizmoLIRC.hpp"
#include "GizmoPowermate.hpp"
#include "GizmoSoundCard.hpp"
#include "GizmoStandard.hpp"
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
#include <fcntl.h>

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
 * \def   USER_SCRIPT_DIR
 * The default path of the modules.d dir
 */
#define USER_SCRIPT_DIR		"modules.d"

/** 
 * \def   SCRIPT_DISPATCHER
 * The path of the initial config script
 */
#define SCRIPT_DISPATCHER 	"GizmodDispatcher.py"

/** 
 * \def   SCRIPT_USER
 * The path of the user config script that gets run after SCRIPT_DISPATCH
 */
#define SCRIPT_USER		"GizmodUser.py"

/** 
 * \def   EVENT_NODE_DIR
 * Default path to the event nodes
 */
#define EVENT_NODE_DIR		"/dev/input"

/** 
 * \def   LIRC_DEV
 * Default path to the LIRC device node
 */
#define LIRC_DEV		"/dev/lirc/0"

////////////////////////////////////////////////////////////////////////////
// Statics
///////////////////////////////////////

boost::mutex GizmoDaemon::mMutexScript;	///< Mutex for the python script

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

	bool		getInitialized() { return python::call_method<bool>(self, "getInitialized"); }
	void		initialize()	 { return python::call_method<void>(self, "initialize"); }
	void		onDeregisterDevice(GizmoCPU const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoLIRC const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoPowermate const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoSoundCard const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoStandard const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onEvent(GizmoEventCPU const * Event, GizmoCPU const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventLIRC const * Event, GizmoLIRC const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventPowermate const * Event, GizmoPowermate const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventSoundCard const * Event, GizmoSoundCard const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventStandard const * Event, GizmoStandard const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventWindowFocus const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }
	GizmoClass	onQueryDeviceType(DeviceInfo DeviceInformation) { return python::call_method<GizmoClass>(self, "onQueryDeviceType", DeviceInformation); };
	void		onRegisterDevice(GizmoCPU const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoLIRC const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoPowermate const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoSoundCard const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoStandard const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }

	PyObject * 	self;		///< Pointer to self
};

/**
 * \brief  Python module definition
 */
BOOST_PYTHON_MODULE(GizmoDaemon) {
	/////////////////////////////////////////////////////////////////////
	// Enum exports
	///////////////////////////////////////
	
	/// GizmoClass enum export
	enum_<GizmoClass>("GizmoClass")
		.value("CPU", 		GIZMO_CLASS_CPU)
		.value("LIRC",	 	GIZMO_CLASS_LIRC)
		.value("Powermate", 	GIZMO_CLASS_POWERMATE)
		.value("SoundCard",	GIZMO_CLASS_SOUNDCARD)
		.value("Standard", 	GIZMO_CLASS_STANDARD)
		;
	
	/// GizmoEventClass enum export
	enum_<GizmoEventClass>("GizmoEventClass")
		.value("CPU", 		GIZMO_EVENTCLASS_CPU)
		.value("LIRC",	 	GIZMO_EVENTCLASS_LIRC)
		.value("Powermate", 	GIZMO_EVENTCLASS_POWERMATE)
		.value("SoundCard",	GIZMO_EVENTCLASS_SOUNDCARD)
		.value("Standard", 	GIZMO_EVENTCLASS_STANDARD)
		.value("WindowFocus",	GIZMO_EVENTCLASS_WINDOWFOCUS)
		;	
	
	/// X11FocusEventType enum export
	enum_<X11FocusEventType>("X11FocusEventType")
		.value("FocusIn", 	X11FOCUSEVENT_IN)
		.value("FocusOut", 	X11FOCUSEVENT_OUT)
		;
	
	/// GizmoEventType and GizmoKey Python Enum Exposures
	#include "GizmoKeyDefPythonExposures.hpp"	
	
	/////////////////////////////////////////////////////////////////////
	// General Class exports
	///////////////////////////////////////
	
	/// DeviceInfo Python Class Export
	class_<DeviceInfo>("GizmoDeviceInfo")
		.def_readonly("DeviceName", &DeviceInfo::DeviceName)
		.def_readonly("DeviceIDBusType", &DeviceInfo::DeviceIDBusType)
		.def_readonly("DeviceIDVendor", &DeviceInfo::DeviceIDVendor)
		.def_readonly("DeviceIDProduct", &DeviceInfo::DeviceIDProduct)
		.def_readonly("DeviceIDVersion", &DeviceInfo::DeviceIDVersion)
		.def_readonly("FileName", &DeviceInfo::FileName)
		;
	
	/// Gizmo Python Class Export
	class_< Gizmo, bases<DeviceInfo> >("Gizmo", init<GizmoClass, const DeviceInfo &>())
		.def("getGizmoClass", &Gizmo::getGizmoClass)
		.add_property("Class", &Gizmo::getGizmoClass)				
		.def("getKeyState", &Gizmo::getGizmoKeyState)
		.def("getGizmoType", &Gizmo::getGizmoType)
		.add_property("Type", &Gizmo::getGizmoType)
		.def("setKeyState", &Gizmo::setGizmoKeyState)
		;
				
	/// GizmoDaemon Python Class Export
	class_<GizmoDaemon>("PyGizmoDaemon")
		.def("getCurrentFocus", &GizmoDaemon::getCurrentFocus)
		.add_property("CurrentFocus", &GizmoDaemon::getCurrentFocus)
		.def("getDebugEnabled", &GizmoDaemon::getDebugEnabled)
		.add_property("DebugEnabled", &GizmoDaemon::getDebugEnabled)
		.def("getVersion", &GizmoDaemon::getVersion)
		.add_property("Version", &GizmoDaemon::getVersion)
		;
	
	/// GizmoTimeVal Python Class Export
	class_<GizmoTimeVal>("GizmoTimeVal")
		.def_readonly("Seconds", &GizmoTimeVal::Seconds)
		.def_readonly("MicroSeconds", &GizmoTimeVal::MicroSeconds)
		;
		
	/////////////////////////////////////////////////////////////////////
	// Event class exports
	///////////////////////////////////////
	
	/// GizmodEventHandlerInterface Python Class Export	
	class_<GizmodEventHandlerInterface, GizmodEventHandlerInterfaceWrap, boost::noncopyable>("GizmodEventHandler")
		;

	/// GizmoEvent Python Class Export
 	class_<GizmoEvent>("GizmoEvent", init<GizmoEventClass>())
		.def("getEventClass", &GizmoEvent::getEventClass)
		.add_property("Class", &GizmoEvent::getEventClass)
		.def("getEventType", &GizmoEvent::getEventType)
		.add_property("EventType", &GizmoEvent::getEventType)
		;
	
	/// GizmoEventCPU Python Class Export
 	class_< GizmoEventCPU, bases<GizmoEvent> >("GizmoEventCPU")
		;
			
	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventLIRC, bases<GizmoEvent> >("GizmoEventLIRC")
		.def_readonly("LIRCData", &GizmoEventLIRC::LIRCData)
		.def_readonly("LIRCDataBitString", &GizmoEventLIRC::LIRCDataBitString)
		;
		
	/// GizmoLinuxInputDevice Python Class Export
	class_<GizmoLinuxInputDevice>("GizmoLinuxInputDevice", init<int>())
		.def("createEvent", &GizmoLinuxInputDevice::createEvent)
		.def("createEvents", &GizmoLinuxInputDevice::createEvents)
		;
	
	/// GizmoLinuxInputEvent Python Class Export
	class_<GizmoLinuxInputEvent>("GizmoLinuxInputEvent")
		.def_readonly("RawCode", &GizmoLinuxInputEvent::RawCode)
		.def_readonly("RawType", &GizmoLinuxInputEvent::RawType)
		.def_readonly("Value", &GizmoLinuxInputEvent::Value)
		.def_readonly("TimeStamp", &GizmoLinuxInputEvent::TimeStamp)
		.def_readonly("Code", &GizmoLinuxInputEvent::Code)
		.def_readonly("Type", &GizmoLinuxInputEvent::Type)
		;
	
	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventPowermate, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventPowermate")
		;

	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventStandard, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventStandard")
		;
			
	/// X11FocusEvent Python Class Export
	class_<X11FocusEvent>("X11FocusEvent", init<X11FocusEvent const &>())
		.def_readonly("WindowEventType", &X11FocusEvent::EventType)
		.def_readonly("WindowClass", &X11FocusEvent::WindowClass)
		.def_readonly("WindowName", &X11FocusEvent::WindowName)
		.def_readonly("WindowNameFormal", &X11FocusEvent::WindowNameFormal)
		;
	
	/// GizmoEventWindowFocus Python Class Export
	class_< GizmoEventWindowFocus, bases<X11FocusEvent, GizmoEvent> >("GizmoEventWindowFocus", init<X11FocusEvent const &>())
		;
		
	/////////////////////////////////////////////////////////////////////
	// Device class exports
	///////////////////////////////////////
	
	/// GizmoLIRC Python Class Export
	class_< GizmoLIRC, bases<Gizmo> >("GizmoLIRC", init<const DeviceInfo &>())
		;
	
	/// GizmoPowermate Python Class Export
	class_< GizmoPowermate, bases<Gizmo, GizmoLinuxInputDevice> >("GizmoPowermate", init<const DeviceInfo &>())
		;

	/// GizmoStandard Python Class Export
	class_< GizmoStandard, bases<Gizmo, GizmoLinuxInputDevice> >("GizmoStandard", init<const DeviceInfo &>())
		;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief  Default Constructor
 */
GizmoDaemon::GizmoDaemon() {
	cout << getProps();
	
	mConfigDir = SCRIPT_DIR;
	mEventsDir = EVENT_NODE_DIR;
	mInitialized = false;
	mLircDev = LIRC_DEV;
	mpPyDispatcher = NULL;
}

/**
 * \brief  Default Destructor
 */
GizmoDaemon::~GizmoDaemon() {
	cdbg << "GizmoDaemon Shutting Down..." << endl << endl;
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Delete a Gizmo
 * \param  FileName The filename of the Gizmo to be deleted
 */
void GizmoDaemon::deleteGizmo(std::string FileName) {
	// remove from map
	shared_ptr<Gizmo> pGizmo = mGizmos[FileName];
	if (!pGizmo) {
		// not found -- unusual, but whatever
		cdbg << "Tried to delete non-existent Gizmo [" << FileName << "]" << endl;
		return; 
	}
	
	// remove the gizmo
	mGizmos.erase(FileName);
	
	// signal python script
	try {
		mutex::scoped_lock lock(mMutexScript);
		switch (pGizmo->getGizmoClass()) {
		case GIZMO_CLASS_CPU:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoCPU const *>(pGizmo.get()));
			break;
 		case GIZMO_CLASS_LIRC:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoLIRC const *>(pGizmo.get()));
			break;
		case GIZMO_CLASS_POWERMATE: 
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoPowermate const *>(pGizmo.get()));
			break; 
		case GIZMO_CLASS_SOUNDCARD:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoSoundCard const *>(pGizmo.get()));
			break;
		case GIZMO_CLASS_STANDARD:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoStandard const *>(pGizmo.get()));
			break;
		}		
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
			PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onEvent");
	}
		
	cdbg << "Deleted Gizmo [" << FileName << "]" << endl;
}

/**
 * \brief  Enter the main run loop
 */
void GizmoDaemon::enterLoop() {
	if (!mInitialized)
		throw H::Exception("You must initialize GizmoDaemon first!", __FILE__, __FUNCTION__, __LINE__);
	
	watchForFileEvents();
}

/**
 * \brief  Get currently focused window
 * \return The X11FocusEvent containing information about the currently focused window
 * 
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".CurrentFocus"
 */
X11FocusEvent GizmoDaemon::getCurrentFocus() {
	return mCurrentFocus;
}

/**
 * \brief  Return whether debug mode is enabled or not
 * \return True if enabled
 * 
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".DebugEnabled"
 */
bool GizmoDaemon::getDebugEnabled() {
	return Debug::getDebugEnabled();
}

/**
 * \brief  Get the event handler / dispatcher
 * \return The dispatcher
 */
GizmodEventHandlerInterface * GizmoDaemon::getDispatcher() {
	return mpPyDispatcher;
}

/**
 * \brief  Get a Gizmo by its file name
 * \param  FileName The filename of the gizmo to find
 * \return The Gizmo (shared_ptr) or a NULL shared_ptr if not found
 */
boost::shared_ptr<Gizmo> GizmoDaemon::getGizmoByFileName(std::string FileName) {
	return mGizmos[FileName];
}

/**
 * \brief  Get the program's propers
 */
string GizmoDaemon::getProps() {
	return "\nGizmoDaemon v" + getVersion() + " -- (c) 2007, Tim Burrell <tim.burrell@gmail.com>\n";
}

/**
 * \brief  Get all the directories inside the user script dir
 *
 * This is for modifying the import path so that users can 
 * create directories inside the user script dir of scripts
 * to be imported
 */
std::string GizmoDaemon::getUserScriptDirPaths() {
	string ret;
	string UserScriptDir = mConfigDir + USER_SCRIPT_DIR;
	cdbg1 << "Adding [" << UserScriptDir << "] to the System Path" << endl;
	path UserScriptPath(UserScriptDir);
	if (!filesystem::exists(UserScriptPath))
		throw H::Exception("User Script dir [" + UserScriptDir + "] does NOT exist or permissions are wrong!", __FILE__, __FUNCTION__, __LINE__);
		
	// now register the event nodes
	// get a file listing
	directory_iterator endItr;
	for (directory_iterator iter(UserScriptDir); iter != endItr; iter ++) {
		if (filesystem::is_directory(*iter))
			ret += "sys.path.insert(0, \"" + iter->string() + "\")\n";
	}
	
	return ret;
}

/**
 * \brief  Get the program's version information
 *
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".Version"
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
	
	// load the user scripts
	try {
		loadUserScripts();
	} catch (H::Exception & e) {
		cerr << e.getExceptionMessage() << endl;
	}
			
	// init the X11FocusWatcher
	X11FocusWatcher::init();
	
	// success
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
		//object MainModule((handle<>(borrowed(PyImport_AddModule("__main__")))));
		mPyMainModule = object((handle<>(borrowed(PyImport_AddModule("__main__")))));
		mPyMainNamespace = mPyMainModule.attr("__dict__");
		
		// add Gizmo Daemon module automatically to the namespace
		object GizmoDaemonModule( (handle<>(PyImport_ImportModule("GizmoDaemon"))) );
		mPyMainNamespace["GizmoDaemon"] = GizmoDaemonModule;
		
		// create a new object so the script can access this object
		scope(GizmoDaemonModule).attr("Gizmod") = ptr(this);
		
		// Modify the PYTHONPATH so import's work
		string PathInsertion = 
			"import sys\nsys.path.insert(0, \"" + mConfigDir + "\")\n" +
			"sys.path.insert(0, \"" + mConfigDir + USER_SCRIPT_DIR + "/\")\n" +
			getUserScriptDirPaths();
		cdbg1 << "Modifying PYTHONPATH:\n" << PathInsertion << endl;
		handle<> ignore_path_exec((PyRun_String(
			PathInsertion.c_str(),
			Py_file_input, mPyMainNamespace.ptr(), mPyMainNamespace.ptr())));
		
		// execute the main script code
		string ScriptFile = mConfigDir + SCRIPT_DISPATCHER;
		cdbg1 << "Executing Dispatcher Python Script [" << ScriptFile << "]..." << endl;
		FILE * ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
		
		// Create the event dispatcher object so we can interact with it
		cdbg1 << "Creating Dispatcher Object" << endl;
		handle<> ignore_dispatcher_exec((PyRun_String(
			"Dispatcher = GizmodDispatcher()\nGizmod.Dispatcher = Dispatcher\n",
			Py_file_input, mPyMainNamespace.ptr(), mPyMainNamespace.ptr())));
		
		// Grab the event dispatcher object so we can interact with it
		mpPyDispatcher = extract<GizmodEventHandlerInterface*>(mPyMainNamespace["Dispatcher"]);
		
		// Initialize the dispatcher object
		mpPyDispatcher->initialize();
							
		// execute the user script code
		ScriptFile = mConfigDir + SCRIPT_USER;
		cdbg1 << "Executing User Python Script [" << ScriptFile << "]..." << endl;
		ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
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
		("lircdev,l",		value<string>(),	"Set LIRC device node (default: " LIRC_DEV ")")
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
		cout << endl;
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
	if (VarMap.count("lircdev")) {
		mLircDev = VarMap["lircdev"].as<string>();
		cdbg << "LIRC Device Node set to [" << VarMap["lircdev"].as<string>() << "]" << endl;
	}

	cout << endl;
	return true;
}

/**
 * \brief Load user scripts
 */
void GizmoDaemon::loadUserScripts() {
	cdbg1 << "Loading User Scripts..." << endl;
	
	path UserScriptPath(mConfigDir + USER_SCRIPT_DIR);
	if (!filesystem::exists(UserScriptPath))
		throw H::Exception("User script directory [" + mConfigDir + USER_SCRIPT_DIR + "] does NOT exist or permissions are wrong!", __FILE__, __FUNCTION__, __LINE__);
		
	// now register the event nodes
	// get a file listing
	std::vector<string> UserScripts;
	directory_iterator endItr;
	for (directory_iterator iter(mConfigDir + USER_SCRIPT_DIR); iter != endItr; iter ++) {
		if ( (!filesystem::is_directory(*iter)) && (!filesystem::symbolic_link_exists(*iter)) ) {
			UserScripts.push_back(iter->leaf());
		}
	}
	
	// sort the list of input event nodes
	sort_all(UserScripts);
	
	// load the user scripts (and lock the mutex)
	mutex::scoped_lock lock(mMutexScript);
	apply_func(UserScripts, &GizmoDaemon::loadUserScriptsFunctor, this);
	cout << endl;
}

/**
 * \brief Load user scripts functor
 * \param UserScript The user script to load
 */
void GizmoDaemon::loadUserScriptsFunctor(std::string UserScript) {
	// Note: Mutex is already locked!
	
	// make sure it's a python script, and remove extension
	size_t dotPos = UserScript.rfind(".py");
	if ( (dotPos == string::npos) || (dotPos != UserScript.length() - 3) )
		return;
	UserScript = UserScript.substr(0, dotPos);
	cdbg1 << "Importing User Script [" << UserScript << "]" << endl;
	
	// Import the module
	try {
		string ImportModuleString = "__import__(\"" + UserScript + "\")\n";
		cdbg2 << "Executing Python Code: " << ImportModuleString << endl;
		handle<> ignore_path_exec((PyRun_String(
			ImportModuleString.c_str(),
			Py_file_input, mPyMainNamespace.ptr(), mPyMainNamespace.ptr())));
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
			PyErr_Print();
		throw H::Exception("Failed to Load User Script [" + UserScript + "]", __FILE__, __FUNCTION__, __LINE__);
	}
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
	cout << "onFileEventDelete [" << FullPath << "] -- " << pWatchee->FileName << endl;
	deleteGizmo(pWatchee->FileName);
}

/**
 * \brief Event triggered when a file is disconnected
 * \param pWatchee The Watchee that triggered the event
 */
void GizmoDaemon::onFileEventDisconnect(boost::shared_ptr<H::FileWatchee> pWatchee) {
	cout << "onFileEventDisconnect [" << pWatchee->FileName << "]: " << pWatchee->DeviceName << endl;
	deleteGizmo(pWatchee->FileName);
}

/**
 * \brief Event triggered when data is waiting on a device
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void GizmoDaemon::onFileEventRead(boost::shared_ptr<H::FileWatchee> pWatchee, DynamicBuffer<char> const & ReadBuffer) {
	// make sure the gizmo exists
	shared_ptr<Gizmo> pUnknownGizmo = mGizmos[pWatchee->FileName];
	if (!pUnknownGizmo) {
		cdbg << "Unknown Event Detected on Device [" << pWatchee->DeviceName << "] of Length [" << (int) ReadBuffer.length() << "]" << endl;
		return;
	}
				
	// create the event and dispatch it
	try {
		switch (pUnknownGizmo->getGizmoClass()) {
		case GIZMO_CLASS_CPU:
			break;
		case GIZMO_CLASS_LIRC: {
			std::vector< boost::shared_ptr<GizmoEventLIRC> > EventVector;
			GizmoLIRC * pGizmo = static_cast<GizmoLIRC const *>(pUnknownGizmo.get());
			GizmoEventLIRC::buildEventsVectorFromBuffer(EventVector, ReadBuffer);
			for (size_t lp = 0; lp < EventVector.size(); lp ++) {
				mutex::scoped_lock lock(mMutexScript);
				pGizmo->processEvent(EventVector[lp].get());
				mpPyDispatcher->onEvent(EventVector[lp].get(), pGizmo);
			}
			break; }
		case GIZMO_CLASS_POWERMATE: {
			std::vector< boost::shared_ptr<GizmoEventPowermate> > EventVector;
			GizmoPowermate * pGizmo = static_cast<GizmoPowermate const *>(pUnknownGizmo.get());
			GizmoEventPowermate::buildEventsVectorFromBuffer(EventVector, ReadBuffer, pGizmo->getSendNullEvents());
			for (size_t lp = 0; lp < EventVector.size(); lp ++) {
				mutex::scoped_lock lock(mMutexScript);
				pGizmo->processEvent(EventVector[lp].get());
				mpPyDispatcher->onEvent(EventVector[lp].get(), pGizmo);
			}
			break; }
		case GIZMO_CLASS_SOUNDCARD: {
			std::vector< boost::shared_ptr<GizmoEventSoundCard> > EventVector;
			GizmoSoundCard * pGizmo = static_cast<GizmoSoundCard const *>(pUnknownGizmo.get());
			//GizmoEventSoundCard::buildEventsVectorFromBuffer(EventVector, ReadBuffer, pGizmo->getSendNullEvents());
			for (size_t lp = 0; lp < EventVector.size(); lp ++) {
				mutex::scoped_lock lock(mMutexScript);
				pGizmo->processEvent(EventVector[lp].get());
				mpPyDispatcher->onEvent(EventVector[lp].get(), pGizmo);
			}
			break; }
		case GIZMO_CLASS_STANDARD: {
			std::vector< boost::shared_ptr<GizmoEventStandard> > EventVector;
			GizmoStandard * pGizmo = static_cast<GizmoStandard const *>(pUnknownGizmo.get());
			GizmoEventStandard::buildEventsVectorFromBuffer(EventVector, ReadBuffer, pGizmo->getSendNullEvents());
			for (size_t lp = 0; lp < EventVector.size(); lp ++) {
				mutex::scoped_lock lock(mMutexScript);
				pGizmo->processEvent(EventVector[lp].get());
				mpPyDispatcher->onEvent(EventVector[lp].get(), pGizmo);
			}
			break; }
		}
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
			PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onEvent");
	}
}

/**
 * \brief Event triggered when a new device is registered
 * \param pWatchee The Watchee that triggered the event
 */
void GizmoDaemon::onFileEventRegister(boost::shared_ptr<H::FileWatchee> pWatchee) {
	cdbg1 << "New Device Detected [" << pWatchee->FileName << "]: " << pWatchee->DeviceName << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoClass Class = mpPyDispatcher->onQueryDeviceType(*pWatchee);
		switch (Class) {
		case GIZMO_CLASS_CPU: {
			shared_ptr<GizmoStandard> pGizmo(new GizmoStandard(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_LIRC: {
			shared_ptr<GizmoLIRC> pGizmo(new GizmoLIRC(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_POWERMATE: {
			shared_ptr<GizmoPowermate> pGizmo(new GizmoPowermate(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_SOUNDCARD: {
			shared_ptr<GizmoSoundCard> pGizmo(new GizmoSoundCard(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_STANDARD: {
			shared_ptr<GizmoStandard> pGizmo(new GizmoStandard(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		}
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
			PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onQueryDeviceType");
	}
}

/**
 * \brief  Event triggered on a Focus In
 * \param  Event The Focus Event
 */
void GizmoDaemon::onFocusIn(X11FocusEvent const & Event) {
	//cdbg << "Current Focus: " << Event.WindowName << " [" << Event.WindowNameFormal << "] <" << Event.WindowClass << ">" << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		mCurrentFocus = Event;
		GizmoEventWindowFocus FocusEvent(Event);
		mpPyDispatcher->onEvent(&FocusEvent);
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
			PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onQueryDeviceType");
	}
}

/**
 * \brief  Event triggered on a Focus Out
 * \param  Event The Focus Event
 */
void GizmoDaemon::onFocusOut(X11FocusEvent const & Event) {
	//cdbg << "Leaving Focus: " << Event.WindowName << " [" << Event.WindowNameFormal << "] <" << Event.WindowClass << ">" << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventWindowFocus FocusEvent(Event);
		mpPyDispatcher->onEvent(&FocusEvent);
	} catch (error_already_set) {
		if (Debug::getDebugEnabled())
			PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onQueryDeviceType");
	}
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
	cdbg1 << "Registering Devices..." << endl;
	
	// register input event devices
	registerInputEventDevices();
	
	// register the LIRC device
	registerLircDevice();
	
	// register CPU usage device
	//registerCPUDevice();
	
	cout << endl;
}

/**
 * \brief  Register all of the input event devices with Gizmo Daemon
 */
void GizmoDaemon::registerInputEventDevices() {
	cdbg1 << "Registering Input Event Devices in [" << mEventsDir << "]" << endl;
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
	apply_func_args(eventsFiles, &FileEventWatcher::addFileToWatch, this, WATCH_INOUT, "Unknown");
}

/**
 * \brief  Register the LIRC device
 */
void GizmoDaemon::registerLircDevice() {
	cdbg1 << "Registering LIRC device node [" << mLircDev << "]" << endl;
	path LircDevPath(mLircDev);
	if (!filesystem::exists(LircDevPath)) {
		cdbg << "LIRC device node [" + mLircDev + "] does not exist -- disabling LIRC support" << endl;
		return;
	}
	int tfd;
	if ((tfd = open(mLircDev.c_str(), O_RDONLY)) == -1) {
		cdbg << "Could not connect to LIRC device node [" + mLircDev + "] -- disabling LIRC support" << endl;
		cdbg << "    - Check permissions" << endl;
		cdbg << "    - Ensure lircd is not running" << endl;
		return;
	}
	close(tfd);
	
	// register the directory itself
	addFileToWatch(mLircDev, WATCH_IN, "LIRC");
}
