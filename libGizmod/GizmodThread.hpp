    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodThread.hpp
*** \brief GizmodThread class header
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

#ifndef __GizmodThread_h
#define __GizmodThread_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

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
 * \class GizmodThread
 * \brief Class for creating threads from the Python API
 *
 * Note that for some reason Python's threading API doesn't
 * work very well embedded inside C++
**/
class GizmodThread {
public:
	// public functions
	void				create();		///< Create a thread and start its execution
	
	// construction / deconstruction	
	GizmodThread(boost::python::object ThreadFunction);	///< Default Constructor
	virtual ~GizmodThread();				///< Destructor

private:
	// private functions
	void				threadProc();		///< thread procedure
	
	// private member variables
	boost::python::object 		mThreadFunction;	///< The thread function
	
	/**
	 * Thread callback procedure struct
	**/
	struct GizmodThreadThreadProc {
		GizmodThreadThreadProc(GizmodThread * pGizmodThread) : mpGizmodThread(pGizmodThread) {
			mpGizmodThread->mThreading = false;
		};
		
		/// Thread proc
		void operator()() {
			mpGizmodThread->mThreading = true;
			mpGizmodThread->threadProc();
			mpGizmodThread->mThreading = false;
		}
		
		GizmodThread * 		mpGizmodThread;///< The associated SoundCard
	};		
	bool				mThreading;	///< Variable to keep track if we're threading or not
	GizmodThreadThreadProc		mThreadProc;	///< The thread procedure instance		
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __GizmodThread_h
