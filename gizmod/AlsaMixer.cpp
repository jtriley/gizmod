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
#include "Alsa.hpp"
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
	if (!pAlsaMixer)
		return 0;
	return pAlsaMixer->mixerElemCallback(MixerElement, EventMask);
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
	// remember the old state
	AlsaMixerElements OldState(*this);
	
	// grab new info from the sound card
	populateInfo();
	
	// fire the event
	AlsaEvent Event(ALSAEVENT_MIXERELEMENT_CHANGE, EventMask);
	AlsaMixerElements::buildEventFromMixerStates(Event, OldState, *this);
	Alsa * pAlsa = static_cast<Alsa *>(mpiAlsa);
	pAlsa->_onAlsaEventMixerElementChange(Event, static_cast<AlsaSoundCard &>(*mpiSoundCard), *this);
	pAlsa->onAlsaEventMixerElementChange(Event, static_cast<AlsaSoundCard &>(*mpiSoundCard), *this);
	
	// success
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  AlsaMixer Default Constructor
 */
AlsaMixer::AlsaMixer() {
	mpiAlsa = NULL;
	mMixerElement = NULL;
	mMixerID = -1;
	mpiSoundCard = NULL;
}	

/** 
 * \brief  AlsaMixer Default Constructor
 */
AlsaMixer::AlsaMixer(AlsaSoundCardInterface * piSoundCard, snd_mixer_elem_t * MixerElement, std::string MixerName, std::string MixerNameUnique, unsigned int MixerID) {
	mpiAlsa = piSoundCard->getAlsa();
	mpiSoundCard = piSoundCard;
	mMixerElement = MixerElement;
	mMixerName = MixerName;	
	mMixerNameUnique = MixerNameUnique;
	mMixerID = MixerID;
	
	init();
}

/**
 * \brief  AlsaMixer Destructor
 */
AlsaMixer::~AlsaMixer() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the unique name of the mixer
 * \return Unique mixer name
 */
std::string AlsaMixer::getName() const {
	return mMixerNameUnique;
}

/**
 * \brief  Get the name of the mixer
 * \return Mixer name
 */
std::string AlsaMixer::getNameShort() const {
	return mMixerName;
}

/**
 * \brief  Initialize the mixer
 */
void AlsaMixer::init() { 
	// fire the event
	static_cast<Alsa *>(mpiAlsa)->onAlsaEventMixerElementAttach(AlsaEvent(ALSAEVENT_MIXERELEMENT_ATTACH), static_cast<AlsaSoundCard &>(*mpiSoundCard), *this);	

	// populate
	populateInfo();
}

/**
 * \brief  Populate the mixer info
 *
 * Load the mixer up with data from the sound card
 */
void AlsaMixer::populateInfo() {
	// get the data
	long tempMin, tempMax, temp;	
	IsActive = snd_mixer_selem_is_active(mMixerElement);
	HasCommonVolume = snd_mixer_selem_has_common_volume(mMixerElement);
	HasPlaybackVolume = snd_mixer_selem_has_playback_volume(mMixerElement);
	HasPlaybackVolumeJoined = snd_mixer_selem_has_playback_volume_joined(mMixerElement);
	HasCaptureVolume = snd_mixer_selem_has_capture_volume(mMixerElement);
	HasCaptureVolumeJoined = snd_mixer_selem_has_capture_volume_joined(mMixerElement);
	HasCommonSwitch = snd_mixer_selem_has_common_switch(mMixerElement);
	HasPlaybackSwitch = snd_mixer_selem_has_playback_switch(mMixerElement);
	HasPlaybackSwitchJoined = snd_mixer_selem_has_playback_switch_joined(mMixerElement);
	HasCaptureSwitch = snd_mixer_selem_has_capture_switch(mMixerElement);
	HasCaptureSwitchJoined = snd_mixer_selem_has_capture_switch_joined(mMixerElement);
	HasCaptureSwitchExclusive = snd_mixer_selem_has_capture_switch_exclusive(mMixerElement);
	
	// Playback volume
	if ( (HasPlaybackVolume) || (HasPlaybackVolumeJoined) || (HasCommonVolume) ) {
		if (snd_mixer_selem_get_playback_volume_range(mMixerElement, &tempMin, &tempMax) >= 0) {
			VolumePlaybackMin = tempMin;
			VolumePlaybackMax = tempMax;
		}
			
		if (snd_mixer_selem_get_playback_volume(mMixerElement, SND_MIXER_SCHN_MONO, &temp) >= 0) {
			// fix for alsa bug!
			if (temp != 0) {
				VolumePlayback = temp;
				VolumePlaybackPercent = (float) (VolumePlayback - VolumePlaybackMin) / (float) (VolumePlaybackMax - VolumePlaybackMin) * 100.0f;
			}
		}
	} else {
		VolumePlaybackMin = VolumePlaybackMax = VolumePlayback = 0;
		VolumePlaybackPercent = 0.0f;
	}

	// Playback switch
	if ( (HasPlaybackSwitch) || (HasPlaybackSwitchJoined) || (HasCommonSwitch) ) {
		int tVal;
		if (snd_mixer_selem_get_playback_switch(mMixerElement, SND_MIXER_SCHN_MONO, &tVal) >= 0)
			SwitchPlayback = tVal;
	} else {
		SwitchPlayback = false;
	}

	// Capture volume
	if ( (HasCaptureVolume) || (HasCaptureVolumeJoined) || (HasCommonVolume) ) {
		if (snd_mixer_selem_get_capture_volume_range(mMixerElement, &tempMin, &tempMax) >= 0) {
			VolumeCaptureMin = tempMin;
			VolumeCaptureMax = tempMax;
		}
			
		if (snd_mixer_selem_get_capture_volume(mMixerElement, SND_MIXER_SCHN_MONO, &temp) >= 0) {
			// fix for alsa bug!
			if (temp != 0) {
				VolumeCapture = temp;
				VolumeCapturePercent = (float) (VolumeCapture - VolumeCaptureMin) / (float) (VolumeCaptureMax - VolumeCaptureMin) * 100.0f;
			}
		}
	} else {
		VolumeCaptureMin = VolumeCaptureMax = VolumeCapture = 0;
		VolumeCapturePercent = 0.0f;
	}

	// Capture switch
	if ( (HasCaptureSwitch) || (HasCaptureSwitchJoined) || (HasCommonSwitch) ) {
		int tVal;
		if (snd_mixer_selem_get_capture_switch(mMixerElement, SND_MIXER_SCHN_MONO, &tVal) >= 0)
			SwitchCapture = tVal;
	} else {
		SwitchCapture = false;
	}
}

/**
 * \brief  Set the capture switch
 * \param  Enable Set to true if the switch should be enabled
 * \return True on success
 */
bool AlsaMixer::setSwitchCapture(bool Enable) {
	if (snd_mixer_selem_set_capture_switch_all(mMixerElement, Enable) < 0)
		return false;
	SwitchCapture = Enable;
	return true;
}

/**
 * \brief  Set the playback switch
 * \param  Enable Set to true if the switch should be enabled
 * \return True on success
 */
bool AlsaMixer::setSwitchPlayback(bool Enable) {
	if (snd_mixer_selem_set_playback_switch_all(mMixerElement, Enable) < 0)
		return false;
	SwitchPlayback = Enable;
	return true;
}

/**
 * \brief  Set the Capture volume
 * \param  Volume Absolute volume level
 * \return True on success
 */
bool AlsaMixer::setVolumeCapture(long Volume) {
	if (Volume < VolumeCaptureMin)
		Volume = VolumeCaptureMin;
	else if (Volume > VolumeCaptureMax) 
		Volume = VolumeCaptureMax;
	if (snd_mixer_selem_set_capture_volume_all(mMixerElement, Volume) < 0)
		return false;
	VolumeCapture = Volume;
	VolumeCapturePercent = float(VolumeCapture - VolumeCaptureMin) / float(VolumeCaptureMax - VolumeCaptureMin) * 100.0f;
	return true;
}

/**
 * \brief  Set the Capture volume as a percent
 * \param  Percent Volume level percentage
 * \return True on success
 */
bool AlsaMixer::setVolumeCapturePercent(float Percent) {
	if (Percent < 0.0f)
		Percent = 0.0f;
	else if (Percent > 100.0f)
		Percent = 100.0f;
	long NewVolume = (long) (Percent / 100.0f * (VolumeCaptureMax - VolumeCaptureMin)) + VolumeCaptureMin;
	if (snd_mixer_selem_set_capture_volume_all(mMixerElement, NewVolume) < 0)
		return false;
	VolumeCapturePercent = Percent;
	VolumeCapture = NewVolume;
	return true;
}

/**
 * \brief  Set the Playback volume
 * \param  Volume Absolute volume level
 * \return True on success
 */
bool AlsaMixer::setVolumePlayback(long Volume) {
	if (Volume < VolumePlaybackMin)
		Volume = VolumePlaybackMin;
	else if (Volume > VolumePlaybackMax) 
		Volume = VolumePlaybackMax;
	if (snd_mixer_selem_set_playback_volume_all(mMixerElement, Volume) < 0)
		return false;
	VolumePlayback = Volume;
	VolumePlaybackPercent = float(VolumePlayback - VolumePlaybackMin) / float(VolumePlaybackMax - VolumePlaybackMin) * 100.0f;
	return true;
}

/**
 * \brief  Set the Playback volume as a percent
 * \param  Percent Volume level percentage
 * \return True on success
 */
bool AlsaMixer::setVolumePlaybackPercent(float Percent) {
	if (Percent < 0.0f)
		Percent = 0.0f;
	else if (Percent > 100.0f)
		Percent = 100.0f;
	long NewVolume = (long) (Percent / 100.0f * (VolumePlaybackMax - VolumePlaybackMin)) + VolumePlaybackMin;
	if (snd_mixer_selem_set_playback_volume_all(mMixerElement, NewVolume) < 0)
		return false;
	VolumePlaybackPercent = Percent;
	VolumePlayback = NewVolume;
	return true;
}

/**
 * \brief  Shutdown the mixer
 */
void AlsaMixer::shutdown() { 
	// fire the event
	static_cast<Alsa *>(mpiAlsa)->onAlsaEventMixerElementDetach(AlsaEvent(ALSAEVENT_MIXERELEMENT_DETACH), static_cast<AlsaSoundCard &>(*mpiSoundCard), *this);	
}
