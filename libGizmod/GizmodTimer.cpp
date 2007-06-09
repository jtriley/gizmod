    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodTimer.cpp
*** \brief GizmodTimer class body
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

#include "GizmodTimer.hpp"
#include "GizmoEventLIRC.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/UtilTime.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////
	
/** 
 * \def    TIMER_GRANULARITY
 * \brief  Amount of time to wait before checking for a cancel
 */
#define	TIMER_GRANULARITY	0.5f

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmodTimer Default Constructor
 */
GizmodTimer::GizmodTimer(float Seconds, boost::python::object TimerFunction) : mThreadProc(this) {
	mCancel = false;
	mSleepTime = Seconds;
	mTimerFunction = TimerFunction;
}

/**
 * \brief GizmodTimer Init Constructor
 */
GizmodTimer::GizmodTimer(float Seconds, boost::python::object TimerFunction, boost::python::object UserData) : mThreadProc(this) {
	mCancel = false;
	mSleepTime = Seconds;
	mTimerFunction = TimerFunction;
	setUserData(UserData);
}

/**
 * \brief GizmodTimer Destructor
 */
GizmodTimer::~GizmodTimer() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Create a thread and start its execution
 */
void GizmodTimer::start() {
	cdbg4 << "GizmodTimer :: start" << endl;
	boost::thread thrd(mThreadProc);
}

/**
 * \brief  Create a thread and start its execution
 */
void GizmodTimer::cancel() {
	cdbg4 << "GizmodTimer :: cancel" << endl;
	mCancel = true;
}

/**
 * \brief  Reset the timer's time
 */
void GizmodTimer::resetTimer() {
	mTotalSlept = 0.0f;
}

/**
 * \brief  Set the Timer's user data
 * \param  UserData User defined data
 */
void GizmodTimer::setUserData(boost::python::object UserData) {
	mUserData = UserData;
}

/** 
 * \brief  The ThreadProc
 */
void GizmodTimer::threadProc() {
	cdbg4 << "GizmodTimer :: Sleeping [" << mSleepTime << "s]" << endl;
	
	// sleep the desired amount of time
	mTotalSlept = 0.0f;
	mCancel = false;
	while ( (!mCancel) && (mTotalSlept < mSleepTime) ) {
		float SleepStep = TIMER_GRANULARITY;
		if (mTotalSlept + SleepStep > mSleepTime)
			SleepStep = mSleepTime - mTotalSlept;
		cdbg5 << "GizmodTimer :: Slept [" << mTotalSlept<< "s] of [" << mSleepTime << "s] -- Sleeping [" << SleepStep << "s]" << endl;
		UtilTime::sleep(SleepStep);
		mTotalSlept += SleepStep + 0.01f;
	}
	
	if (mCancel) {
		cdbg5 << "GizmodTimer :: Cancel Called" << endl;
		return;
	}		
	
	// call the python timer function
	cdbg4 << "GizmodTimer :: Calling Python timerFunction" << endl;
	mTimerFunction(mUserData);
	
	cdbg5 << "GizmodTimer :: Python timerFunction exited." << endl;
}
