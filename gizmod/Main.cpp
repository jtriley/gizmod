    /**
  *********************************************************************
*************************************************************************
*** 
*** \file    Main.cpp
*** \brief   Gizmod Main Program
*** \author  Tim Burrell -- tim.burrell@gmail.com
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

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Main.hpp"
#include "GizmoDaemon.hpp"
#include "../libH/Exception.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/operations.hpp>

using namespace std;
using namespace H;
using namespace boost;
using namespace boost::filesystem;

/**
 * \brief  main function for the program
 * \param  argc number of command line arguments
 * \param  argv command line arguments
 * \return success value
 *
 * Instantiate the main object, and run
 */
int main (int argc, char * argv []) {
	// set filesystem to native filesystem checking
	path::default_name_check(native);
	
	// create the Gizmod
	shared_ptr<GizmoDaemon> pGizmod(new GizmoDaemon);
	
	// try initializing
	try {
		if (!pGizmod->initialize(argc, argv))
			return EXIT_SUCCESS;
	} catch (H::Exception & e) {
		cerr << "\nUnable to Initialize Gizmod :: " << e.message() << "\n\n";
		return EXIT_FAILURE;
	}
	
	// Setup
	try {
		pGizmod->initGizmod();
	} catch (H::Exception & e) {
		cerr << "Unable to Initialize Gizmod :: " << e.message() << "\n\n";
		return EXIT_FAILURE;
	}
	
	// enter the run loop
	try {
		pGizmod->enterLoop();
	} catch (H::Exception & e) {
		cerr << "Fatal Error :: " << e.message() << "\n\n";
		return EXIT_FAILURE;
	}
		
	return EXIT_SUCCESS;
}
