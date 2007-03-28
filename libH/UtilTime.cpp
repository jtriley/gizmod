    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  UtilTime.cpp
*** \brief UtilTime class body
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

#include "UtilTime.hpp"
#include "../libH/Debug.hpp"
#include <sys/time.h>

using namespace H;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * Constructor
 */
UtilTime::UtilTime() {
	updateElapsedTimer();
}

/**
 * Destructor
 */
UtilTime::~UtilTime() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \return cpu ticks
 *
 * Get the current number of cpu ticks in microseconds
 */
unsigned long UtilTime::getTicks() {
	struct timeval tv;
	gettimeofday(&tv, NULL);

	/*
	* This will wrap around approximately every 4000 seconds, i.e.
	* just over an hour, which is more than enough.
	*/
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

/**
 * \brief Get time since last update
 * \param UpdateTimer update the timer at the same time
 *
 * Get the elapsed time since last update and update the timer if desired
 */
unsigned long UtilTime::getElapsedTime() {
	return getTicks() - mLastUpdate;
}

/**
 * \brief  wrapper for nanosleep
 * \return actual time slept
 * 
 * sleep a number of nanoseconds
 */
int UtilTime::nanoSleep(int nanoSecs) {
	struct 	timespec sleepTime;
	struct 	timespec sleepRet;

	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = nanoSecs;
	sleepRet.tv_sec = 0;
	sleepRet.tv_nsec = 0;
	
	nanosleep(&sleepTime, &sleepRet);
	
	return sleepRet.tv_nsec;
}

/**
 * \brief  wrapper for nanosleep which sleeps in seconds
 * \return actual time slept
 * 
 * Sleep a number of seconds using the nanosleep function
 */
int UtilTime::nanoSleepSecs(int nanoSecs) {
	struct 	timespec sleepTime;
	struct 	timespec sleepRet;

	sleepTime.tv_sec = nanoSecs;
	sleepTime.tv_nsec = 0;
	sleepRet.tv_sec = 0;
	sleepRet.tv_nsec = 0;
	
	nanosleep(&sleepTime, &sleepRet);
	
	return sleepRet.tv_nsec;
}

/**
 * Update the time duration watcher
 */
void	UtilTime::updateElapsedTimer() {
	mLastUpdate = getTicks();
}
