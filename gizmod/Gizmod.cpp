    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Gizmod.cpp
*** \brief Gizmod class body
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

#include "Gizmod.hpp"
#include "GizmodPyInterface.hpp"
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
// C++ -> Python Exposures
///////////////////////////////////////

BOOST_PYTHON_MODULE(GizmoDaemon) {
 	class_<GizmodPyInterface>("Gizmod")
		.def("getVersion", & GizmodPyInterface::getVersion);
}

////////////////////////////////////////////////////////////////////////////
// Type Defs / defines
///////////////////////////////////////

/** 
 * \def   CONFIG_FILE
 * The default path of the config file
 */
#define CONFIG_FILE		PACKAGE_NAME ".conf"

/** 
 * \def   SCRIPT_FILE
 * The default path of the config file
 */
#define SCRIPT_FILE		PACKAGE_NAME ".py"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
Gizmod::Gizmod() {
	cout << getProps();
	
	mConfigScript = SCRIPT_FILE;
}

/**
 * \brief Default Destructor
 */
Gizmod::~Gizmod() {
	cdbg << "Gizmod Shutting Down..." << endl << endl;
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Enter the main run loop
 */
void Gizmod::enterLoop() {
}

/**
 * \brief Get the program's propers
 */
string Gizmod::getProps() {
	return "\nGizmod v" + getVersion() + " -- (c) 2007, Tim Burrell <tim.burrell@gmail.com>\n";
}

/**
 * \brief Get the program's version information
 */
string Gizmod::getVersion() {
	return string(PACKAGE_VERSION);
}

/**
 * \brief  Setup Gizmod
 * 
 * Initialize Gizmod
 */
void Gizmod::initGizmod() {
	// TODO init gizmod
	
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
void Gizmod::initPython() {
	try {
		cdbg1 << "Embedding Python Interpreter..." << endl;
		PyImport_AppendInittab("GizmoDaemon", &initGizmoDaemon);
		Py_Initialize();
		
		cdbg << "Executing Python Script..." << endl;
		object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object main_namespace = main_module.attr("__dict__");
		
		// add Gizmo Daemon module automatically to the namespace
		object GizmoDaemonModule( (handle<>(PyImport_ImportModule("GizmoDaemon"))) );
		main_namespace["GizmoDaemon"] = GizmoDaemonModule;
				
		/*
		handle<> ignored(( PyRun_String( "print \"Hello, World\"",
			Py_file_input,
			main_namespace.ptr(), main_namespace.ptr() ) ));
		*/
		
		FILE * ifScript = fopen(mConfigScript.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + mConfigScript + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, mConfigScript.c_str());
		
		// create the object instance 
		//object PyBase = PythonDerived();
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
bool Gizmod::initialize(int argc, char ** argv) {
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
		("config,c",		value<string>(),	"Set config file script")
		;
        
        // hiGizmodn options
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
	if (VarMap.count("config")) {
		mConfigScript = VarMap["config"].as<string>();
		cdbg << "Config Script set to [" << VarMap["config"].as<string>() << "]" << endl;
	}

	cout << endl;
	return true;
}
