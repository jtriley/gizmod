    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodThread.cpp
*** \brief GizmodThread class body
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

#include "GizmodThread.hpp"
#include "GizmoEventLIRC.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/UtilTime.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost;
using namespace H;
using namespace Gizmod;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////
	
////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmodThread Default Constructor
 */
GizmodThread::GizmodThread(boost::python::object ThreadFunction) : mThreadProc(this) {
	mThreadFunction = ThreadFunction;
}

/**
 * \brief GizmodThread Destructor
 */
GizmodThread::~GizmodThread() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Create a thread and start its execution
 */
void GizmodThread::create() {
	cdbg4 << "GizmodThread :: create" << endl;
	boost::thread thrd(mThreadProc);
}

/** 
 * \brief  The ThreadProc
 */
void GizmodThread::threadProc() {
	cdbg4 << "GizmodThread :: Calling Python threadFunction" << endl;
	
	// call the python thread function
	mThreadFunction();
	
	cdbg4 << "GizmodThread :: Python threadFunction exited." << endl;
}
