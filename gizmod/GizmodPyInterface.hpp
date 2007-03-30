    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodPyInterface.hpp
*** \brief GizmodPyInterface class header file
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

#ifndef __GizmodPyInterface_h
#define __GizmodPyInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmodPyInterface
 * \brief Main GizmodPyInterface class
 */
class GizmodPyInterface {
public:
	// public functions
	std::string			getVersion();		///< Get version string
		
	// construction / deconstruction
	GizmodPyInterface();
	virtual ~GizmodPyInterface();

private:
};

#endif // __GizmodPyInterface_h
