    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventSoundCard.cpp
*** \brief GizmoEventSoundCard class body
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

#include "GizmoEventSoundCard.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

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
 * \brief GizmoEventSoundCard Default Constructor
**/
GizmoEventSoundCard::GizmoEventSoundCard(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, bool IsRemote) : 
	AlsaEvent(Event),
	GizmoEvent(GIZMO_EVENTCLASS_SOUNDCARD, IsRemote)
{
	mpSoundCard = &SoundCard;
	mpMixer = NULL;
}

/**
 * \brief GizmoEventSoundCard Default Constructor
**/
GizmoEventSoundCard::GizmoEventSoundCard(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer, bool IsRemote) : 
	AlsaEvent(Event),
	GizmoEvent(GIZMO_EVENTCLASS_SOUNDCARD, IsRemote)
{
	mpSoundCard = &SoundCard;
	mpMixer = &Mixer;
}

/**
 * \brief GizmoEventSoundCard Serialize Constructor
**/
GizmoEventSoundCard::GizmoEventSoundCard() {
}

/**
 * \brief GizmoEventSoundCard Destructor
**/
GizmoEventSoundCard::~GizmoEventSoundCard() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the associated Mixer
 * \return The Mixer
**/
AlsaMixer const * GizmoEventSoundCard::getMixer() {
	return mpMixer;
}

/**
 * \brief  Get the associated SoundCard
 * \return The SoundCard
**/
AlsaSoundCard const * GizmoEventSoundCard::getSoundCard() {
	return mpSoundCard;
}
