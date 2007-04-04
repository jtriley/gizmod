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
 * \brief Default Constructor
 */
UtilTime::UtilTime() {
	updateElapsedTimer();
}

/**
 * \brief Destructor
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
