    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaInterface.hpp
*** \brief AlsaInterface header
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

#ifndef __AlsaInterface_h
#define __AlsaInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

/*
#include "AlsaEvent.hpp"
#include "AlsaSoundCard.hpp"
#include "AlsaMixer.hpp"
*/

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// AlsaInterface Class Definition
///////////////////////////////////////

/**
 * \class  AlsaInterface
 * \brief  Interface to the Alsa class
 */
class AlsaInterface {
public:	
	// public functions
	/*
	virtual void			onAlsaEventSoundCardAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard) = 0; ///< Triggered when a new sound card is detected
	virtual void			onAlsaEventSoundCardDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard) = 0; ///< Triggered when a sound card is removed
	virtual void			onAlsaEventMixerElementAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) = 0; ///< Triggered when a mixer element is discovered
	*/

	// construction / deconstruction
	AlsaInterface();
	virtual ~AlsaInterface();
	
	// public static functions

private:
	// private functions
		
	// private member variables
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __AlsaInterface_h
