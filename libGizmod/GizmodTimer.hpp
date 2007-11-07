    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodTimer.hpp
*** \brief GizmodTimer class header
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

#ifndef __GizmodTimer_h
#define __GizmodTimer_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmodShared.hpp"
#include <boost/python.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmodTimer
 * \brief Class for creating threads from the Python API
 *
 * Note that for some reason Python's threading API doesn't
 * work very well embedded inside C++
**/
class GizmodTimer : public GizmodShared {
public:
	// public functions
	void				cancel();		///< Cancel a timer's execution
	void				resetTimer();		///< Reset the timer's time
	void				setUserData(boost::python::object UserData); ///< Set the Timer's user data
       	void				setTime(float Seconds);	///< Set the time to sleep before firing timer event
	void				start();		///< Start a timer's execution
	
	// construction / deconstruction	
	GizmodTimer(float Seconds, boost::python::object TimerFunction); ///< Default Constructor
	GizmodTimer(float Seconds, boost::python::object TimerFunction, boost::python::object UserData); ///< Init Constructor
	GizmodTimer(float Seconds, boost::python::object TimerFunction, int Repeats, boost::python::object UserData); ///< Init Constructor
	virtual ~GizmodTimer();					///< Destructor

private:
	// private functions
	void				threadProc();		///< thread procedure
	
	// private member variables
	bool				mCancel;		///< Cancel Timer
	int				mRepeats;		///< Number of times the timer has repeated
	float				mSleepTime;		///< Amount of time to sleep between firings
	boost::python::object 		mTimerFunction;		///< The Timer function
	int				mTotalRepeats;		///< Times to repeat
	float				mTotalSlept;		///< Total time slept so far
	boost::python::object 		mUserData;		///< User Data for the Timer function
	
	/**
	 * Thread callback procedure struct
	**/
	struct GizmodTimerThreadProc {
		GizmodTimerThreadProc(GizmodTimer * pGizmodTimer) : mpGizmodTimer(pGizmodTimer) {
			mpGizmodTimer->mThreading = false;
		};
		
		/// Thread proc
		void operator()() {
			mpGizmodTimer->mThreading = true;
			mpGizmodTimer->threadProc();
			mpGizmodTimer->mThreading = false;
		}
		
		GizmodTimer * 		mpGizmodTimer;///< The associated SoundCard
	};		
	bool				mThreading;	///< Variable to keep track if we're threading or not
	GizmodTimerThreadProc		mThreadProc;	///< The thread procedure instance		
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __GizmodTimer_h
