    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Gizmod.hpp
*** \brief Gizmod class header file
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

#ifndef __Gizmod_h
#define __Gizmod_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Gizmod
 * \brief Main Gizmod class
 */
class Gizmod {
public:
	// public functions
	void				enterLoop();		///< Enter the main run loop
	void				initGizmod();		///< Initialize Gizmod Evolution
	bool				initialize(int argc, char ** argv); ///< generic init stuff, command line, etc
		
	Gizmod();
	virtual ~Gizmod();

private:
	// private functions
	std::string	 		getProps();		///< Get version information
	
	// private member vars
	std::string			mConfigScript;		///< Configuration Script
};

#endif // __Gizmod_h
