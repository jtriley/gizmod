    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventWindowFocus.cpp
*** \brief GizmoEventWindowFocus class body
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

#include "GizmoEventWindowFocus.hpp"
#include "GizmoLinuxInputDevice.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/Util.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;
using namespace H;
using namespace Gizmod;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoEventWindowFocus Default Constructor
 */
GizmoEventWindowFocus::GizmoEventWindowFocus(X11FocusEvent const & Event, bool IsRemote) : X11FocusEvent(Event), GizmoEvent(GIZMO_EVENTCLASS_WINDOWFOCUS, false) {
}

/**
 * \brief GizmoEventWindowFocus Serialize Constructor
 */
GizmoEventWindowFocus::GizmoEventWindowFocus() {
}

/**
 * \brief GizmoEventWindowFocus Destructor
 */
GizmoEventWindowFocus::~GizmoEventWindowFocus() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////
