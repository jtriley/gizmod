    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  UtilTime.hpp
*** \brief UtilTime class header file
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

#ifndef __UtilTime_h
#define __UtilTime_h

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
 * \class UtilTime
 * \brief Main UtilTime class
 *
 * This class provides static time routines for sleeping and finding the current time
 *
 * It also can be instantiated to provide a time duration watcher
 */
class UtilTime {
public:
	unsigned long 		getElapsedTime();			///< get the elapsed time
	static unsigned long	getTicks();				///< get the current number of cpu ticks in usecs
	static int 		nanoSleep(int nanoSecs);		///< sleep a number of nanoseconds
	static int 		nanoSleepSecs(int seconds);		///< sleep a number of seconds
	void			updateElapsedTimer();			///< update the time duration watcher
	
	UtilTime();
	virtual ~UtilTime();

private:
	unsigned long		mLastUpdate;				///< time since last update
};

} // H namespace

#endif // __UtilTime_h
