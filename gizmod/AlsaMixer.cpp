    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaMixer.cpp
*** \brief AlsaMixer Class Body
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

#include "AlsaMixer.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Callbacks
///////////////////////////////////////

/** 
 * \brief  Public static MixerElement callback function
 * \param  MixerElement Mixer element handle
 * \param  EventMask event mask
 * \return 0 on success otherwise a negative error code
 *
 * Just pass off the event to the appropriate AlsaSoundCard instantiation
 */
int AlsaMixer::MixerElemCallback(snd_mixer_elem_t * MixerElement, unsigned int EventMask) {
	AlsaMixer * pAlsaMixer = static_cast<AlsaMixer *>(snd_mixer_elem_get_callback_private(MixerElement));
	return pAlsaMixer->mixerElemCallback(MixerElement, EventMask);
	/*
	if (!ppAlsaMixer)
		return 0;
	shared_ptr<AlsaMixer> & pAlsaMixer = *ppAlsaMixer;
	if (pAlsaMixer)
		return pAlsaMixer->mixerElemCallback(MixerElement, EventMask);
	*/
	return 0;
}

/** 
 * \brief  MixerElement callback function
 * \param  MixerElement Mixer element handle
 * \param  EventMask event mask
 * \return 0 on success otherwise a negative error code
 *
 * Handle the mixer element event
 */
int AlsaMixer::mixerElemCallback(snd_mixer_elem_t * MixerElement, unsigned int EventMask) {
	cdbg << "Mixer Event on [" << mMixerNameUnique << "] <" << EventMask << "> on Card [" << mpiSoundCard->getCardName() << "]" << endl;
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  AlsaMixer Default Constructor
 */
AlsaMixer::AlsaMixer(AlsaSoundCardInterface * piSoundCard, snd_mixer_elem_t * MixerElement, std::string MixerName, std::string MixerNameUnique, unsigned int MixerID) {
	mpiSoundCard = piSoundCard;
	mMixerElement = MixerElement;
	mMixerName = MixerName;	
	mMixerNameUnique = MixerNameUnique;
	mMixerID = MixerID;
}

/**
 * \brief  AlsaMixer Destructor
 */
AlsaMixer::~AlsaMixer() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the name of the mixer
 * \return Mixer name
 */
std::string AlsaMixer::getMixerName() {
	return mMixerName;
}
