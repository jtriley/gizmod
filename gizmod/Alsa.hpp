    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Alsa.hpp
*** \brief Alsa header
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

#ifndef __Alsa_h
#define __Alsa_h

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

//////////////////////////////////////////////////////////////////////////////
// AlsaSoundCard Class Definition
///////////////////////////////////////

/**
 * \class  AlsaSoundCard
 * \brief  Data structure that holds information about each Sound Card
 */
class AlsaSoundCard {
public:	
	// public member variables
	
	// public functions

	// construction / deconstruction
	AlsaSoundCard(int CardID);
	virtual ~AlsaSoundCard();

private:
	// private functions
	void				init();			///< Initialize the AlsaSoundCard
	void				shutdown();		///< Shutdown the AlsaSoundCard connection
		
	// private member variables
	int				mCardID;		///< ID of the card
	std::string			mCardHWID;		///< Ascii HW ID of the card
	std::string			mCardName;		///< Name of the card
	std::string			mCardNameLong;		///< Long Name of the card
	snd_ctl_t *			mCTLHandle;		///< Alsa control interface handle
	snd_ctl_card_info_t * 		mHWInfo;		///< Alsa card hardware info
};

//////////////////////////////////////////////////////////////////////////////
// Alsa Class Definition
///////////////////////////////////////

/**
 * \class  Alsa
 * \brief  Watches for focus changes on X11 windows
 */
class Alsa {
public:	
	// public functions
	void				init();			///< Initialize Alsa
	void				shutdown();		///< Shutdown the Alsa connection

	// construction / deconstruction
	Alsa();
	virtual ~Alsa();
	
	// public static functions

private:
	// private functions
		
	// private member variables
	std::vector< boost::shared_ptr<AlsaSoundCard> >	mSoundCards; ///< Vector of sound card control interface handles
};

#endif // __Alsa_h
