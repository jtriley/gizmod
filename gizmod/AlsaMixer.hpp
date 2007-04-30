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

#include "AlsaMixerElements.hpp"
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
 * \brief  Data structure that holds information about each Mixer
 */
class AlsaMixer : public AlsaMixerElements {
public:	
	// public member variables
	
	// public functions
	std::string			getName() const;		///< Get the unique name of the mixer	
	std::string			getNameShort() const;		///< Get the short name of the mixer (not unique)
	bool				setSwitchCapture(bool Enable);	///< Set the capture switch
	bool				setSwitchPlayback(bool Enable);	///< Set the playback switch
	bool				setVolumeCapture(long Volume); 	///< Set the Capture volume
	bool				setVolumeCapturePercent(float Percent); ///< Set the Capture volume as a percent
	bool				setVolumeCaptureDB(long DB);	///< Set the Capture dB
	bool				setVolumePlayback(long Volume); ///< Set the playback volume 
	bool				setVolumePlaybackPercent(float Percent); ///< Set the playback volume as a percent
	bool				setVolumePlaybackDB(long DB);	///< Set the playback dB

	// construction / deconstruction
	AlsaMixer();
	AlsaMixer(AlsaSoundCardInterface * piSoundCard, snd_mixer_elem_t * MixerElement, std::string MixerName, std::string MixerNameUnique, unsigned int MixerID);
	virtual ~AlsaMixer();
	
	// public static functions
	static int 			MixerElemCallback(snd_mixer_elem_t * MixerElement, unsigned int EventMask); ///< Static mixer element callback

private:
	// private functions
	void				init();				///< Initialize the mixer
	int 				mixerElemCallback(snd_mixer_elem_t * MixerElement, unsigned int EventMask); ///< Mixer element callback
	void 				populateInfo();			///< Load the mixer up with data from the sound card
	void				shutdown();			///< Shutdown the mixer
		
	// private member variables
	AlsaInterface *			mpiAlsa;			///< The Alsa object responsible for this mixer
	snd_mixer_elem_t * 		mMixerElement;			///< The Alsa mixer element
	std::string 			mMixerName;			///< Short name of the mixer
	std::string 			mMixerNameUnique;		///< Unique name of the mixer
	unsigned int			mMixerID;			///< ID of the mixer
	AlsaSoundCardInterface *	mpiSoundCard;			///< Associated sound card
};

#endif // __AlsaMixer_h
