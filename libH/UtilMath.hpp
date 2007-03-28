    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  UtilMath.hpp
*** \brief UtilMath class header file
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

#ifndef __UtilMath_h
#define __UtilMath_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

/**
 * \namespace H
 * \brief H namespace
 *
 * This class belongs to libH
 */
namespace H {

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class UtilMath
 * \brief Main UtilMath class
 *
 * This class provides static time routines for sleeping and finding the current time
 *
 * It also can be instantiated to provide a time duration watcher
 */
class UtilMath {
public:
	static int 		intDivRoundUp(int Div1, int Div2);		///< integer divide and round up
	static float 		random();					///< get a random float
	static float 		randomFloat(float MinVal, float MaxVal);	///< get a random float 
	static int		randomInt(int MinVal, int MaxVal);		///< get a random int
	static void		randomize();					///< randomize via the clock
	
	UtilMath();
	virtual ~UtilMath();
};

} // H namespace

#endif // __UtilMath_h
