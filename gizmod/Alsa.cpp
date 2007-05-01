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
#include <string>

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
	mpDefaultMixerSwitch = NULL;
	mpDefaultMixerVolume = NULL;
	mDefaultMixerVolumePriority = -1;
	mDefaultMixerSwitchPriority = -1;
	mMuted = false;
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
 * \brief  Get the system's default mixer for muting
 * \return The desired AlsaMixer
 */
AlsaMixer const * Alsa::getDefaultMixerSwitch() {
	return mpDefaultMixerSwitch;
}

/**
 * \brief  Get the system's default mixer for volume
 * \return The desired AlsaMixer
 */
AlsaMixer const * Alsa::getDefaultMixerVolume() {
	return mpDefaultMixerVolume;
}

/**
 * \brief  Get a sound card by index
 */
AlsaSoundCard const * Alsa::getSoundCard(int Index) {
	if ( (Index < 0) || (size_t(Index) >= mSoundCards.size()) )
		return NULL;
	return mSoundCards[Index].get();
}

/**
 * \brief  Initialize ALSA
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
 * \brief  Triggered when a mixer element is changed -- internal use
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 *
 * This is for setting the references to the default volume and mute mixers
 */
void Alsa::_onAlsaEventMixerElementChange(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer & Mixer) {
	// get the priority of the current mixer element
	int Priority = INT_MAX, CurPriority = 0;
	for (list<string>::iterator iter = mDefaultMixerPriorities.begin(); iter != mDefaultMixerPriorities.end(); iter ++, CurPriority ++) {
		if (stringconverter::toLower(Mixer.getName()) == stringconverter::toLower(*iter)) {
			Priority = CurPriority;
			break;
		}
	}
	
	// set defulat mixer volume
	if ( (!mpDefaultMixerVolume) || (Priority < mDefaultMixerVolumePriority) ) {
		if (Mixer.HasPlaybackVolume) {
			cdbg << "Setting Default Mixer Volume: " << Mixer.getName() << endl;
			mpDefaultMixerVolume = &Mixer;
			mDefaultMixerVolumePriority = Priority;
		}
	} else if ( (mpDefaultMixerVolume == &Mixer) && (!Mixer.HasPlaybackVolume) ) {
		mpDefaultMixerVolume = NULL;
	}

	// set defulat mixer volume
	if ( (!mpDefaultMixerSwitch) || (Priority < mDefaultMixerSwitchPriority) ) {
		if (Mixer.HasPlaybackSwitch) {
			cdbg << "Setting Default Mixer Switch: " << Mixer.getName() << endl;
			mpDefaultMixerSwitch = &Mixer;
			mDefaultMixerSwitchPriority = Priority;
		}
	} else if ( (mpDefaultMixerSwitch == &Mixer) && (!Mixer.HasPlaybackSwitch) ) {
		mpDefaultMixerSwitch = NULL;
	}
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
 * \brief  Register a default mixer priority
 * \param  MixerName Name of the mixer to add
 *
 * Ie, If the default mixer list contains ["master", "pcm"] then if the 
 * Master mixing element has a playback volume, but no mute switch, and 
 * the PCM channel has playback volume and a mute switch, 
 * Gizmod.DefaultMixerVolume will be the Master mixer,
 * and Gizmod.DefaultMixerSwitch will be the PCM mixer.
 */
void Alsa::registerDefaultMixerPriority(std::string MixerName) {
	cdbg1 << "Registering Default Mixer Priority: " << MixerName << endl;
	mDefaultMixerPriorities.push_back(MixerName);
}

/**
 * \brief Shutdown the ALSA connection
 */
void Alsa::shutdown() {
	if (mSoundCards.size())
		cdbg1 << "Shutting down [" << mSoundCards.size() << "] sound card connections..." << endl;
	mSoundCards.clear();
}

/**
 * \brief  Toggle muting on all cards / mixers
 *
 * Shhh...
 */
void Alsa::toggleMuteAllCards() {
	for (size_t lp = 0; lp < mSoundCards.size(); lp ++)
		mSoundCards[lp]->setAllPlaybackSwitches(mMuted);
	mMuted = !mMuted;
}
