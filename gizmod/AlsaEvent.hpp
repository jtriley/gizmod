    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaEvent.hpp
*** \brief AlsaEventheader
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

#ifndef __AlsaEvent_h
#define __AlsaEvent_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <vector>
#include <alsa/asoundlib.h>
#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

/**
 * \enum   AlsaEventType
 * \brief  Type that indicates the type of AlsaEvent
 */
typedef enum {
	ALSAEVENT_MIXER_CHANGE
} AlsaEventType;

//////////////////////////////////////////////////////////////////////////////
// AlsaEvent Class Definition
///////////////////////////////////////

/**
 * \class  AlsaEvent
 * \brief  Data structure that holds information about Alsa events
 */
class AlsaEvent {
public:	
	// public member variables
	AlsaEventType			EventType;		///< The type of event
	
	// public functions

	// construction / deconstruction
	AlsaEvent();
	AlsaEvent(AlsaEventType eventType);
	AlsaEvent(AlsaEvent const & Event);
	virtual ~AlsaEvent();

private:
	// private functions
		
	// private member variables
};

#endif // __AlsaEvent_h
