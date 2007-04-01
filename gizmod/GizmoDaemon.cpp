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
All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "GizmoDaemon.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/python.hpp>

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace boost::python;
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
 * \def   SCRIPT_GizmoDaemon
 * The path of the initial config script
 */
#define SCRIPT_GIZMO_DAEMON	"Gizmod.py"

/** 
 * \def   SCRIPT_USER
 * The path of the user config script that gets run after SCRIPT_GizmoDaemon
 */
#define SCRIPT_USER		"User.py"

/** 
 * \def   EVENT_NODE_DIR
 * Default path to the event nodes
 */
#define EVENT_NODE_DIR		"/dev/input/event"

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

	PyObject * 	self;		///< Pointer to self
};

/**
 * Python module definition
 */
BOOST_PYTHON_MODULE(GizmoDaemon) {
 	class_<GizmoDaemon>("PyGizmoDaemon")
		.def("getVersion", & GizmoDaemon::getVersion)
		;
	
	class_<GizmodEventHandlerInterface, GizmodEventHandlerInterfaceWrap, boost::noncopyable>("GizmodEventHandler")
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
	// TODO init GizmoDaemon
	
	
	// init python
	try {
		initPython();
	} catch (H::Exception & e) {
		throw e;
	} catch (exception & e) {
		throw H::Exception("Failed to Initialize Python!", __FILE__, __FUNCTION__, __LINE__);
	}
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
		string ScriptFile = mConfigDir + SCRIPT_GIZMO_DAEMON;
		cdbg << "Executing Main Python Script [" << ScriptFile << "]..." << endl;
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
	} catch (exception e) {
		cout << VisibleOptions;
		throw H::Exception("Invalid Command Line Argument(s)");
	}

	// try parsing the config file
	try {
		ifstream ifs(CONFIG_FILE);
		store(parse_config_file(ifs, ConfigFileOptions), VarMap);
	} catch (exception e) {
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
