    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventATIX10.hpp
*** \brief GizmoEventATIX10 class header
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

#ifndef __GizmoEventATIX10_h
#define __GizmoEventATIX10_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEvent.hpp"
#include "GizmoLinuxInputEvent.hpp"
#include <string>
#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEventATIX10
 * \brief Class for ATIX10 events
 *
 * This class is for all GizmoEventATIX10s attached to the system.
 */
class GizmoEventATIX10 : public GizmoEvent, public GizmoLinuxInputEvent {
public:
	// public functions
	
	// static public functions
	static void			buildEventsVectorFromBuffer(std::vector< boost::shared_ptr<GizmoEventATIX10> > & EventVector, H::DynamicBuffer<char> const & Buffer, bool SendNullEvents); ///< Build an event list from a read buffer
	
	// construction / deconstruction
	GizmoEventATIX10();						///< Default Constructor
	GizmoEventATIX10(struct input_event const & InputEvent);	///< Init Constructor
	virtual ~GizmoEventATIX10();					///< Destructor

protected:
	// private functions
	
	// private member variables
	
	// static private functions
	static void 			buildEventsVectorFromBufferFunctor(struct input_event & InputEvent, std::vector< boost::shared_ptr<GizmoEventATIX10> > * pEventVector, bool SendNullEvents); ///< Functor for building the events list
};

#endif // __GizmoEventATIX10_h
