    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaMixer.hpp
*** \brief AlsaMixer header
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

#ifndef __AlsaMixer_h
#define __AlsaMixer_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "AlsaSoundCardInterface.hpp"
#include <string>
#include <vector>
#include <alsa/asoundlib.h>

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// AlsaMixer Class Definition
///////////////////////////////////////

/**
 * \class  AlsaMixer
 * \brief  Data structure that holds information about each Mixer element
 */
class AlsaMixer{
public:	
	// public member variables
	std::string			getMixerName();
	
	// public functions

	// construction / deconstruction
	AlsaMixer(AlsaSoundCardInterface * piSoundCard, snd_mixer_elem_t * MixerElement, std::string MixerName, std::string MixerNameUnique, unsigned int MixerID);
	virtual ~AlsaMixer();
	
	// public static functions
	static int 			MixerElemCallback(snd_mixer_elem_t * MixerElement, unsigned int EventMask); ///< Static mixer element callback

private:
	// private functions
	int 				mixerElemCallback(snd_mixer_elem_t * MixerElement, unsigned int EventMask); ///< Mixer element callback
		
	// private member variables
	snd_mixer_elem_t * 		mMixerElement;
	std::string 			mMixerName;
	std::string 			mMixerNameUnique;
	unsigned int			mMixerID;
	AlsaSoundCardInterface *	mpiSoundCard;
};

#endif // __AlsaMixer_h
