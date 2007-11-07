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

#ifndef __UtilTime_h
#define __UtilTime_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

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
**/
class UtilTime {
public:
	unsigned long 		getElapsedTime();			///< get the elapsed time
	static unsigned long	getTicks();				///< get the current number of cpu ticks in usecs
	static int 		nanoSleep(int nanoSecs);		///< sleep a number of nanoseconds
	static int 		nanoSleepSecs(int seconds);		///< sleep a number of seconds
	static void		sleep(float Seconds);			///< sleep a number of seconds (expressed as a float)
	void			updateElapsedTimer();			///< update the time duration watcher
	
	UtilTime();
	virtual ~UtilTime();

private:
	unsigned long		mLastUpdate;				///< time since last update
};

} // H namespace

#endif // __UtilTime_h
