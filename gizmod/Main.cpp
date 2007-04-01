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

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Main.hpp"
#include "GizmoDaemon.hpp"
#include "../libH/Exception.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace H;
using namespace boost;

/**
 * \brief  main function for the program
 * \param  argc number of command line arguments
 * \param  argv command line arguments
 * \return success value
 *
 * Instantiate the main object, and run
 */
int main (int argc, char * argv []) {
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
