    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaEvent.cpp
*** \brief AlsaEvent Class Body
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

#include "AlsaEvent.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  AlsaEvent Default Constructor
 */
AlsaEvent::AlsaEvent() {
	EventType = ALSAEVENT_MIXER_CHANGE;
}

/** 
 * \brief  AlsaEvent Init Constructor
 */
AlsaEvent::AlsaEvent(AlsaEventType eventType) {
	EventType = eventType;
}

/** 
 * \brief  AlsaEvent Init Constructor
 */
AlsaEvent::AlsaEvent(AlsaEvent const & Event) {
	EventType = Event.EventType;
}

/**
 * \brief  AlsaEvent Destructor
 */
AlsaEvent::~AlsaEvent() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////
