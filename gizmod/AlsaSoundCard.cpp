    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaSoundCard.cpp
*** \brief AlsaSoundCard Class Body
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
#include "AlsaSoundCard.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/stringconverter.hpp"
#include <boost/format.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

/**
 * \def    CARD_NAME_UNKNOWN
 * \brief  Text that gets applied if a card's name is not known
 */
#define CARD_NAME_UNKNOWN	"Unknown"

////////////////////////////////////////////////////////////////////////////
// Callbacks
///////////////////////////////////////

/** 
 * \brief  Public static mixer callback function
 * \param  Mixer Mixer handle
 * \param  EventMask event mask
 * \param  MixerElement related mixer element (if any)
 * \return 0 on success otherwise a negative error code
 *
 * Just pass off the event to the appropriate alsa instantiation
 */
int AlsaSoundCard::MixerCallback(snd_mixer_t * Mixer, unsigned int EventMask, snd_mixer_elem_t * MixerElement) {
	AlsaSoundCard * pAlsaSoundCard = static_cast<AlsaSoundCard*>(snd_mixer_get_callback_private(Mixer));
	if (pAlsaSoundCard)
		return pAlsaSoundCard->mixerCallback(Mixer, EventMask, MixerElement);
	return 0;
}

/** 
 * \brief  Mixer callback function
 * \param  Mixer Mixer handle
 * \param  EventMask event mask
 * \param  MixerElement related mixer element (if any)
 * \return 0 on success otherwise a negative error code
 *
 * Just watch for Add events, and set up element callbacks that way
 */
int AlsaSoundCard::mixerCallback(snd_mixer_t * Mixer, unsigned int EventMask, snd_mixer_elem_t * MixerElement) {
	if (EventMask && SND_CTL_EVENT_MASK_ADD) {
		unsigned int MixerIndex = snd_mixer_selem_get_index(MixerElement);
		const char * MixerName = snd_mixer_selem_get_name(MixerElement);
		string MixerNameUnique = MixerIndex ? str(format("%1% %2%") % MixerName % MixerIndex) : MixerName;
		// check for duplicates
		if (mMixers.count(MixerNameUnique)) {
			cdbg << "Mixer [" << MixerNameUnique << "] Duplicated on Card [" << mCardName << "]" << endl;
			return 0;
		}
		shared_ptr<AlsaMixer> pMixer(new AlsaMixer(this, MixerElement, MixerName, MixerNameUnique, MixerIndex));
		mMixers.insert(make_pair(MixerNameUnique, pMixer));
						
		// set the callback
		snd_mixer_elem_set_callback_private(MixerElement, pMixer.get());
		snd_mixer_elem_set_callback(MixerElement, AlsaMixer::MixerElemCallback);
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  AlsaSoundCard Default Constructor
 */
AlsaSoundCard::AlsaSoundCard(AlsaInterface * piAlsa, int CardID) : AlsaSoundCardInterface(piAlsa), mThreadProc(this) {
	mCardID = CardID;
	mCTLHandle = NULL;
	mHWInfo = NULL;
	mMixerHandle = NULL;
	mWatching = false;
	init();
}

/**
 * \brief  AlsaSoundCard Destructor
 */
AlsaSoundCard::~AlsaSoundCard() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the card's hardware ID
 * \return Hardware ID
 */
std::string AlsaSoundCard::getCardHardwareID() const {
	return mCardHWID;
}

/**
 * \brief  Get the card ID
 * \return Card ID
 */
int AlsaSoundCard::getCardID() const {
	return mCardID;
}

/**
 * \brief  Get the name of the card
 * \return Card name
 */
std::string AlsaSoundCard::getCardName() const {
	return mCardName;
}

/**
 * \brief  Get the long name of the card
 * \return Card's long name
 */
std::string AlsaSoundCard::getCardNameLong() const {
	return mCardNameLong;
}

/**
 * \brief  Get a mixer element by index
 * \return The requested AlsaMixer
 */
AlsaMixer const * AlsaSoundCard::getMixer(std::string Name) {
	if (!mMixers.count(Name))
		return NULL;
	return mMixers[Name].get();
}

/**
 * \brief  Initialize The AlsaSoundCard
 */
void AlsaSoundCard::init() {
	if (mWatching) {
		cdbg << "AlsaSoundCard already watching!!" << endl;
		return;
	}
		 
	// set hardware identifier
	mCardHWID = str(format("hw:%1%") % mCardID);
	
	// get the card name
	char * Name;
	if (snd_card_get_name(mCardID, &Name) == -1) {
		mCardName = CARD_NAME_UNKNOWN;
		cdbg << "Failed to retreive name of Sound Card [" << mCardID << "]" << endl;
	} else
		mCardName = Name;

	// long name
	if (snd_card_get_longname(mCardID, &Name) == -1) {
		mCardNameLong = CARD_NAME_UNKNOWN;
		cdbg << "Failed to retreive long name of Sound Card [" << mCardID << "]" << endl;
	} else
		mCardNameLong = Name;
			
		
	// initialize
	cdbg1 << "Initializing Connection to Sound Card [" << mCardName << "]" << endl;	
	int err;
	if ((err = snd_ctl_open(&mCTLHandle, mCardHWID.c_str(), 0)) < 0) 
		throw H::Exception("Could not open Control Interface Handle on Card [" + mCardName + "] -- " + snd_strerror(err), __FILE__, __FUNCTION__, __LINE__);

	snd_ctl_card_info_alloca(&mHWInfo);
	if ((err = snd_ctl_card_info(mCTLHandle, mHWInfo)) < 0)
     		throw H::Exception("Could not Query Card Information on Card [" + mCardName + "] -- " + snd_strerror(err), __FILE__, __FUNCTION__, __LINE__);
	
	// attach a mixer and watch for events on it
	if ((err = snd_mixer_open(&mMixerHandle, 0)) < 0) 
     		throw H::Exception("Could not Open Mixer on Card [" + mCardName + "] -- " + snd_strerror(err), __FILE__, __FUNCTION__, __LINE__);	
		
	if ((err = snd_mixer_attach(mMixerHandle, mCardHWID.c_str())) < 0) 
     		throw H::Exception("Could not Attach to Mixer on Card [" + mCardName + "] -- " + snd_strerror(err), __FILE__, __FUNCTION__, __LINE__);
		
	if ((err = snd_mixer_selem_register(mMixerHandle, NULL, NULL)) < 0)
		throw H::Exception("Could not Register Mixer on Card [" + mCardName + "] -- " + snd_strerror(err), __FILE__, __FUNCTION__, __LINE__);
	
	// fire the event
	static_cast<Alsa *>(mpiAlsa)->onAlsaEventSoundCardAttach(AlsaEvent(ALSAEVENT_SOUNDCARD_ATTACH), *this);
	
	// set the callback
	snd_mixer_set_callback_private(mMixerHandle, (void*) this);
	snd_mixer_set_callback(mMixerHandle, MixerCallback);
	
	if ((err = snd_mixer_load(mMixerHandle)) < 0)
     		throw H::Exception("Could not Load Mixer on Card [" + mCardName + "] -- " + snd_strerror(err), __FILE__, __FUNCTION__, __LINE__);
	
	// initialize the event handler thread
	boost::thread thrd(mThreadProc);
}

/**
 * \brief  Shutdown the AlsaSoundCard connection
 */
void AlsaSoundCard::shutdown() {
	cdbg1 << "Closing connection to Sound Card [" << mCardHWID << " - " << mCardName << "]" << endl;
	mWatching = false;
			
	// shut down alsa connection to the sound card
	if (mMixerHandle)
		snd_mixer_close(mMixerHandle); mMixerHandle = NULL;
	
	if (mCTLHandle)
		snd_ctl_close(mCTLHandle); mCTLHandle = NULL;	
	
	// clear the mixers
	mMixers.clear();	
	
	// fire the event
	static_cast<Alsa *>(mpiAlsa)->onAlsaEventSoundCardDetach(AlsaEvent(ALSAEVENT_SOUNDCARD_DETACH), *this);	
}

/**
 * \brief  The thread procedure loop
 *
 * Wait for events, and tell alsa to dispatch its own events
 */
void AlsaSoundCard::threadProc() {
	// wait for events to occur
	int err;
	mWatching = true;
	while (mWatching) {
		if ((err = snd_mixer_wait(mMixerHandle, -1)) < 0) {
			cout << "test err: " << snd_strerror(err) << endl;
		} else {
			snd_mixer_handle_events(mMixerHandle);
		}
	}
}
