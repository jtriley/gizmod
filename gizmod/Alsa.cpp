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
#include <boost/format.hpp>

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

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  Alsa Default Constructor
 */
Alsa::Alsa() {
}

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
 * \brief  AlsaSoundCard Default Constructor
 */
AlsaSoundCard::AlsaSoundCard(int CardID) {
	mCardID = CardID;
	mCTLHandle = NULL;
	mHWInfo = NULL;
	init();
}

/**
 * \brief  Alsa Destructor
 */
Alsa::~Alsa() {
	shutdown();
}

/**
 * \brief  AlsaEvent Destructor
 */
AlsaEvent::~AlsaEvent() {
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
			shared_ptr<AlsaSoundCard> pSoundCard = shared_ptr<AlsaSoundCard>(new AlsaSoundCard(CardID));
			mSoundCards.push_back(pSoundCard);		
		}
	} while (ret != -1);
}

/**
 * \brief Initialize The AlsaSoundCard
 */
void AlsaSoundCard::init() {
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
 * \brief Shutdown the AlsaSoundCard connection
 */
void AlsaSoundCard::shutdown() {
	cdbg1 << "Closing connection to Sound Card [" << mCardHWID << " - " << mCardName << "]" << endl;
	/* SEGFAULTS
	if (mHWInfo)
		snd_ctl_card_info_free(mHWInfo);
	mHWInfo = NULL;
	*/
	if (mCTLHandle)
		snd_ctl_close(mCTLHandle);
	mCTLHandle = NULL;
}
