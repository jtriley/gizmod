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
#include "GizmoEventPowermate.hpp"
#include "GizmoEventStandard.hpp"
#include "GizmoPowermate.hpp"
#include "GizmoCPU.hpp"
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
	void		onDeregisterDevice(GizmoPowermate const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoStandard const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onEvent(GizmoEventCPU const * Event, GizmoCPU const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventPowermate const * Event, GizmoPowermate const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventStandard const * Event, GizmoStandard const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	GizmoClass	onQueryDeviceType(DeviceInfo DeviceInformation) { return python::call_method<GizmoClass>(self, "onQueryDeviceType", DeviceInformation); };
	void		onRegisterDevice(GizmoCPU const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoPowermate const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoStandard const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }

	PyObject * 	self;		///< Pointer to self
};

/**
 * \brief Python module definition
 */
BOOST_PYTHON_MODULE(GizmoDaemon) {
	/////////////////////////////////////////////////////////////////////
	// Enum exports
	///////////////////////////////////////
	
	/// GizmoClass enum export
	enum_<GizmoClass>("GizmoClass")
		.value("CPU", 		GIZMO_CLASS_CPU)
		.value("Powermate", 	GIZMO_CLASS_POWERMATE)
		.value("LIRC",	 	GIZMO_CLASS_LIRC)
		.value("ATIX10",	GIZMO_CLASS_ATIX10)
		.value("Standard", 	GIZMO_CLASS_STANDARD)
		;	
	
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
		.add_property("GizmoClass", &Gizmo::getGizmoClass)				
		.def("getGizmoType", &Gizmo::getGizmoType)
		.add_property("GizmoType", &Gizmo::getGizmoType)
		;
				
	/// GizmoDaemon Python Class Export
	class_<GizmoDaemon>("PyGizmoDaemon")
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
 	class_<GizmoEvent>("GizmoEvent")
		.def("getEventType", &GizmoEvent::getEventType)
		.add_property("EventType", &GizmoEvent::getEventType)
		;
	
	/// GizmoEventCPU Python Class Export
 	class_< GizmoEventCPU, bases<GizmoEvent> >("GizmoEventCPU")
		;
	
	/// GizmoLinuxInputEvent Python Class Export
	class_<GizmoLinuxInputEvent>("GizmoLinuxInputEvent")
		.def_readonly("RawCode", &GizmoLinuxInputEvent::RawCode)
		.def_readonly("RawType", &GizmoLinuxInputEvent::RawType)
		.def_readonly("RawValue", &GizmoLinuxInputEvent::RawValue)
		.def_readonly("TimeStamp", &GizmoLinuxInputEvent::TimeStamp)
		;
	
	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventPowermate, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventPowermate")
		;

	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventStandard, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventStandard")
		;
		
	/////////////////////////////////////////////////////////////////////
	// Device class exports
	///////////////////////////////////////
	
	/// GizmoPowermate Python Class Export
	class_< GizmoPowermate, bases<Gizmo> >("GizmoPowermate", init<const DeviceInfo &>())
		;

	/// GizmoStandard Python Class Export
	class_< GizmoStandard, bases<Gizmo> >("GizmoStandard", init<const DeviceInfo &>())
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
 * \brief Delete a Gizmo
 * \param FileName The filename of the Gizmo to be deleted
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
		switch (pGizmo->getGizmoClass()) {
		case GIZMO_CLASS_STANDARD:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoStandard const *>(pGizmo.get()));
			break;
		case GIZMO_CLASS_POWERMATE: 
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoPowermate const *>(pGizmo.get()));
			break; 
 		case GIZMO_CLASS_LIRC:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoStandard const *>(pGizmo.get()));
			break;
		case GIZMO_CLASS_ATIX10:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoStandard const *>(pGizmo.get()));
			break;
		case GIZMO_CLASS_CPU:
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
 * \brief Enter the main run loop
 */
void GizmoDaemon::enterLoop() {
	if (!mInitialized)
		throw H::Exception("You must initialize GizmoDaemon first!", __FILE__, __FUNCTION__, __LINE__);
	
	watchForFileEvents();
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
 * \brief Get the program's propers
 */
string GizmoDaemon::getProps() {
	return "\nGizmoDaemon v" + getVersion() + " -- (c) 2007, Tim Burrell <tim.burrell@gmail.com>\n";
}

/**
 * \brief Get the program's version information
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
		
		// Modify the PYTHONPATH so import's work
		string PathInsertion = "import sys\nsys.path.insert(0, \"" + mConfigDir + "\")\n";
		cdbg1 << "Modifying PYTHONPATH:\n" << PathInsertion << endl;
		handle<> ignore_path_exec((PyRun_String(
			PathInsertion.c_str(),
			Py_file_input, MainNamespace.ptr(), MainNamespace.ptr())));
		
		// execute the main script code
		string ScriptFile = mConfigDir + SCRIPT_DISPATCHER;
		cdbg << "Executing Dispatcher Python Script [" << ScriptFile << "]..." << endl;
		FILE * ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
		
		// Create the event dispatcher object so we can interact with it
		cdbg1 << "Creating Dispatcher Object" << endl;
		handle<> ignore_dispatcher_exec((PyRun_String(
			"Dispatcher = GizmodDispatcher()\n",
			Py_file_input, MainNamespace.ptr(), MainNamespace.ptr())));
		
		// Grab the event dispatcher object so we can interact with it
		mpPyDispatcher = extract<GizmodEventHandlerInterface*>(MainNamespace["Dispatcher"]);
		
		// Initialize the dispatcher object
		mpPyDispatcher->initialize();
							
		// execute the user script code
		ScriptFile = mConfigDir + SCRIPT_USER;
		cdbg << "Executing User Python Script [" << ScriptFile << "]..." << endl;
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
	cout << "onFileEventDelete [" << FullPath << "] -- " << pWatchee->FileName << endl;
	//deleteGizmo(pWatchee->FileName);
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
		case GIZMO_CLASS_STANDARD: {
			std::vector< boost::shared_ptr<GizmoEventStandard> > EventVector;
			GizmoStandard * pGizmo = static_cast<GizmoStandard const *>(pUnknownGizmo.get());
			GizmoEventStandard::buildEventsVectorFromBuffer(EventVector, ReadBuffer, pGizmo->getSendNullEvents());
			for (size_t lp = 0; lp < EventVector.size(); lp ++)
				mpPyDispatcher->onEvent(EventVector[lp].get(), pGizmo);
			break; }
		case GIZMO_CLASS_POWERMATE: {
			std::vector< boost::shared_ptr<GizmoEventPowermate> > EventVector;
			GizmoPowermate * pGizmo = static_cast<GizmoPowermate const *>(pUnknownGizmo.get());
			GizmoEventPowermate::buildEventsVectorFromBuffer(EventVector, ReadBuffer, pGizmo->getSendNullEvents());
			for (size_t lp = 0; lp < EventVector.size(); lp ++)
				mpPyDispatcher->onEvent(EventVector[lp].get(), static_cast<GizmoPowermate const *>(pUnknownGizmo.get()));
			break; }
		case GIZMO_CLASS_LIRC:
			break;
		case GIZMO_CLASS_ATIX10:
			break;
		case GIZMO_CLASS_CPU:
			break;
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
	cdbg << "New Device Detected [" << pWatchee->FileName << "]: " << pWatchee->DeviceName << endl;
	try {
		GizmoClass Class = mpPyDispatcher->onQueryDeviceType(*pWatchee);
		switch (Class) {
		case GIZMO_CLASS_STANDARD: {
			shared_ptr<GizmoStandard> pGizmo(new GizmoStandard(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_POWERMATE: {
			shared_ptr<GizmoPowermate> pGizmo(new GizmoPowermate(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_LIRC: {
			shared_ptr<GizmoStandard> pGizmo(new GizmoStandard(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_ATIX10: {
			shared_ptr<GizmoStandard> pGizmo(new GizmoStandard(*pWatchee));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_CPU: {
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
