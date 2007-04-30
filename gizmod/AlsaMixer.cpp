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
	static_cast<Alsa *>(mpiAlsa)->onAlsaEventMixerElementChange(Event, static_cast<AlsaSoundCard &>(*mpiSoundCard), *this);
	
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
	mpiSoundCard = NULL;
	mMixerElement = NULL;
	mMixerID = -1;
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
	
	// playback volume
	if ( (HasPlaybackVolume) || (HasPlaybackVolumeJoined) || (HasCommonVolume) ) {
		snd_mixer_selem_get_playback_volume_range(mMixerElement, &VolumePlaybackMin, &VolumePlaybackMax);
		snd_mixer_selem_get_playback_volume(mMixerElement, SND_MIXER_SCHN_MONO, &VolumePlayback);
		snd_mixer_selem_get_playback_dB_range(mMixerElement, &VolumePlaybackDBMin, &VolumePlaybackDBMax);
		snd_mixer_selem_get_playback_dB(mMixerElement, SND_MIXER_SCHN_MONO, &VolumePlaybackDB);
		VolumePlaybackPercent = (float) (VolumePlayback - VolumePlaybackMin) / (float) (VolumePlaybackMax - VolumePlaybackMin) * 100.0f;
	} else {
		VolumePlaybackMin = VolumePlaybackMax = VolumePlayback = 0;
		VolumePlaybackPercent = 0.0f;
	}
		
	// capture volume
	if ( (HasCaptureVolume) || (HasCaptureVolumeJoined) || (HasCommonVolume) ) {
		snd_mixer_selem_get_capture_volume_range(mMixerElement, &VolumeCaptureMin, &VolumeCaptureMax);
		snd_mixer_selem_get_capture_volume(mMixerElement, SND_MIXER_SCHN_MONO, &VolumeCapture);
		snd_mixer_selem_get_capture_dB_range(mMixerElement, &VolumeCaptureDBMin, &VolumeCaptureDBMax);
		snd_mixer_selem_get_capture_dB(mMixerElement, SND_MIXER_SCHN_MONO, &VolumeCaptureDB);
		VolumeCapturePercent = (float) (VolumeCapture - VolumeCaptureMin) / (float) (VolumeCaptureMax - VolumeCaptureMin) * 100.0f;
	} else {
		VolumeCaptureMin = VolumeCaptureMax = VolumeCapture = 0;
		VolumeCapturePercent = 0.0f;
	}

	// playback switch
	int tVal;
	if ( (HasPlaybackSwitch) || (HasPlaybackSwitchJoined) || (HasCommonSwitch) ) {
		snd_mixer_selem_get_playback_switch(mMixerElement, SND_MIXER_SCHN_MONO, &tVal);
		SwitchPlayback = tVal;
	} else {
		SwitchPlayback = false;
	}
	
	// capture switch
	if ( (HasCaptureSwitch) || (HasCaptureSwitchJoined) || (HasCommonSwitch) ) {
		snd_mixer_selem_get_capture_switch(mMixerElement, SND_MIXER_SCHN_MONO, &tVal);
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
	populateInfo();
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
	populateInfo();
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
	populateInfo();
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
	else if (Percent > 1.0f)
		Percent = 1.0f;
	if (snd_mixer_selem_set_capture_volume_all(mMixerElement, (long) (Percent / 100.0f * (VolumeCaptureMax - VolumeCaptureMin)) + VolumeCaptureMin) < 0)
		return false;
	populateInfo();
	return true;
}

/**
 * \brief  Set the Capture volume as a dB
 * \param  DB Volume level dB
 * \return True on success
 */
bool AlsaMixer::setVolumeCaptureDB(long DB) {
	if (DB < VolumeCaptureDBMin)
		DB = VolumeCaptureDBMin;
	else if (DB > VolumeCaptureDBMax)
		DB = VolumeCaptureDBMax;
	if (snd_mixer_selem_set_capture_dB_all(mMixerElement, DB, 0) < 0)
		return false;
	populateInfo();
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
	populateInfo();
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
	else if (Percent > 1.0f)
		Percent = 1.0f;
	if (snd_mixer_selem_set_playback_volume_all(mMixerElement, (long) (Percent / 100.0f * (VolumePlaybackMax - VolumePlaybackMin)) + VolumePlaybackMin) < 0)
		return false;
	populateInfo();
	return true;
}

/**
 * \brief  Set the Playback volume as a dB
 * \param  DB Volume level dB
 * \return True on success
 */
bool AlsaMixer::setVolumePlaybackDB(long DB) {
	if (DB < VolumePlaybackDBMin)
		DB = VolumePlaybackDBMin;
	else if (DB > VolumePlaybackDBMax)
		DB = VolumePlaybackDBMax;
	if (snd_mixer_selem_set_playback_dB_all(mMixerElement, DB, 0) < 0)
		return false;
	populateInfo();
	return true;
}

/**
 * \brief  Shutdown the mixer
 */
void AlsaMixer::shutdown() { 
	// fire the event
	static_cast<Alsa *>(mpiAlsa)->onAlsaEventMixerElementDetach(AlsaEvent(ALSAEVENT_MIXERELEMENT_DETACH), static_cast<AlsaSoundCard &>(*mpiSoundCard), *this);	
}
