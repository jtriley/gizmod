    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Alsa.cpp
*** \brief Alsa Class Body
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

#include "Alsa.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/stringconverter.hpp"
#include <boost/format.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  Alsa Default Constructor
 */
Alsa::Alsa() {
}

/**
 * \brief  Alsa Destructor
 */
Alsa::~Alsa() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Initialize ALSA
 */
void Alsa::init() {
	// first make sure the connections are closed
	shutdown();
	
	// initialize
	int ret = -1, CardID;
	do {
		// get the next sound card
		if ((CardID = snd_card_next(&ret)) < 0) {
			cerr << "Failed to Query Sound Card [" << ret + 1 << "] -- Error Code: " << CardID;
			continue;
		}
		if (ret > -1) {
			shared_ptr<AlsaSoundCard> pSoundCard = shared_ptr<AlsaSoundCard>(new AlsaSoundCard(this, CardID));
			mSoundCards.push_back(pSoundCard);
		}
	} while (ret != -1);
}

/**
 * \brief  Triggered when a mixer element is discovered
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 */
void Alsa::onAlsaEventMixerElementAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) {
	// override me
	cdbg1 << "Mixer Element Attached [" << Mixer.getName() << "] on Sound Card [" << SoundCard.getCardName() << "]" << endl;
}

/**
 * \brief  Triggered when a mixer element is changed
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 */
void Alsa::onAlsaEventMixerElementChange(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) {
	// override me
	if (Event.Type == ALSAEVENT_MIXERELEMENT_CHANGE) 
		cdbg2 << "Mixer Element Changed [" << Mixer.getName() << "] with Mask [" << stringconverter(Event.IsActiveChanged) << stringconverter(Event.ElementsChanged) << stringconverter(Event.VolumePlaybackChanged) << "] on Sound Card [" << SoundCard.getCardName() << "] " << Mixer.VolumePlaybackPercent << endl;
	else
		cdbg2 << "Mixer Element Changed [" << Mixer.getName() << "] with Mask [" << Event.Mask << "] on Sound Card [" << SoundCard.getCardName() << "]" << endl;
}

/**
 * \brief  Triggered when a mixer element is detached
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 */
void Alsa::onAlsaEventMixerElementDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) {
	// override me
	cdbg3 << "Mixer Element Detached [" << Mixer.getName() << "] on Sound Card [" << SoundCard.getCardName() << "]" << endl;
}

/**
 * \brief  Triggered when a new sound card is detected
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 */
void Alsa::onAlsaEventSoundCardAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard) {
	// override me
	cdbg << "Attached to Sound Card [" << SoundCard.getCardHardwareID() << "] -- " << SoundCard.getCardName() << endl;
}

/**
 * \brief  Triggered when a sound card is removed
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 */
void Alsa::onAlsaEventSoundCardDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard) {
	// override me
	cdbg1 << "Sound Card Detached [" << SoundCard.getCardHardwareID() << "] -- " << SoundCard.getCardName() << endl;
}

/**
 * \brief Shutdown the ALSA connection
 */
void Alsa::shutdown() {
	if (mSoundCards.size())
		cdbg1 << "Shutting down [" << mSoundCards.size() << "] sound card connections..." << endl;
	mSoundCards.clear();
}
