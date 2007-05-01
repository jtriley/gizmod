    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaMixerElements.cpp
*** \brief AlsaMixerElements Class Body
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

#include "AlsaMixerElements.hpp"
#include "Alsa.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  AlsaMixerElements Default Constructor
 */
AlsaMixerElements::AlsaMixerElements() {
	IsActive = false;
	HasCommonVolume = false;
	HasPlaybackVolume = false;
	HasPlaybackVolumeJoined = false;
	HasCaptureVolume = false;
	HasCaptureVolumeJoined = false;
	HasCommonSwitch = false;
	HasPlaybackSwitch = false;
	HasPlaybackSwitchJoined = false;
	HasCaptureSwitch = false;
	HasCaptureSwitchJoined = false;
	HasCaptureSwitchExclusive = false;
	
	VolumePlayback = 0;
	VolumePlaybackMin = 0;
	VolumePlaybackMax = 0;
	VolumePlaybackPercent = 0.0f;

	VolumeCapture = 0;
	VolumeCaptureMin = 0;
	VolumeCaptureMax = 0;
	VolumeCapturePercent = 0.0f;
	
	SwitchPlayback = false;
	SwitchCapture = false;
}

/** 
 * \brief  AlsaMixerElements Init Constructor
 */
AlsaMixerElements::AlsaMixerElements(AlsaMixerElements const & Init) {
	IsActive = Init.IsActive;
	HasCommonVolume = Init.HasCommonVolume;
	HasPlaybackVolume = Init.HasPlaybackVolume;
	HasPlaybackVolumeJoined = Init.HasPlaybackVolumeJoined;
	HasCaptureVolume = Init.HasCommonVolume;
	HasCaptureVolumeJoined = Init.HasCaptureVolumeJoined;
	HasCommonSwitch = Init.HasCommonSwitch;
	HasPlaybackSwitch = Init.HasPlaybackSwitch;
	HasPlaybackSwitchJoined = Init.HasPlaybackSwitchJoined;
	HasCaptureSwitch = Init.HasCaptureSwitch;
	HasCaptureSwitchJoined = Init.HasCaptureSwitchJoined;
	HasCaptureSwitchExclusive = Init.HasCaptureSwitchExclusive;
	
	VolumePlayback = Init.VolumePlayback;
	VolumePlaybackMin = Init.VolumePlaybackMin;
	VolumePlaybackMax = Init.VolumePlaybackMax;
	VolumePlaybackPercent = Init.VolumePlaybackPercent;

	VolumeCapture = Init.VolumeCapture;
	VolumeCaptureMin = Init.VolumeCaptureMin;
	VolumeCaptureMax = Init.VolumeCaptureMax;
	VolumeCapturePercent = Init.VolumeCapturePercent;

	SwitchPlayback = Init.SwitchPlayback;
	SwitchCapture = Init.SwitchCapture;
}

/**
 * \brief  AlsaMixerElements Destructor
 */
AlsaMixerElements::~AlsaMixerElements() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Build an event from two mixer states
 * \param  Event The return event
 * \param  OldElements The old mixer state
 * \param  NewElements The new mixer state
 */
void AlsaMixerElements::buildEventFromMixerStates(AlsaEvent & Event, AlsaMixerElements const & OldElements, AlsaMixerElements const & NewElements) {
	Event.IsActiveChanged = false;
	Event.ElementsChanged = false;
	Event.VolumePlaybackChanged = false;
	Event.SwitchCaptureChanged = false;
	Event.SwitchPlaybackChanged = false;
	
	if (OldElements.IsActive != NewElements.IsActive)
		Event.IsActiveChanged = true;
	
	if ( (OldElements.HasCommonVolume != NewElements.HasCommonVolume) ||
	     (OldElements.HasPlaybackVolume != NewElements.HasPlaybackVolume) ||
	     (OldElements.HasPlaybackVolumeJoined != NewElements.HasPlaybackVolumeJoined) ||
	     (OldElements.HasCaptureVolume != NewElements.HasCommonVolume) ||
	     (OldElements.HasCaptureVolumeJoined != NewElements.HasCaptureVolumeJoined) ||
	     (OldElements.HasCommonSwitch != NewElements.HasCommonSwitch) ||
	     (OldElements.HasPlaybackSwitch != NewElements.HasPlaybackSwitch) ||
	     (OldElements.HasPlaybackSwitchJoined != NewElements.HasPlaybackSwitchJoined) ||
	     (OldElements.HasCaptureSwitch != NewElements.HasCaptureSwitch) ||
	     (OldElements.HasCaptureSwitchJoined != NewElements.HasCaptureSwitchJoined) ||
	     (OldElements.HasCaptureSwitchExclusive != NewElements.HasCaptureSwitchExclusive) ) {
		Event.ElementsChanged = true;
	}
		
	if ( (OldElements.VolumePlayback != NewElements.VolumePlayback) ||
	     (OldElements.VolumePlaybackMin != NewElements.VolumePlaybackMin) ||
	     (OldElements.VolumePlaybackMax != NewElements.VolumePlaybackMax) ) {
		Event.VolumePlaybackChanged = true;
	}

	if ( (OldElements.VolumeCapture != NewElements.VolumeCapture) ||
	     (OldElements.VolumeCaptureMin != NewElements.VolumeCaptureMin) ||
	     (OldElements.VolumeCaptureMax != NewElements.VolumeCaptureMax) ) {
		Event.VolumeCaptureChanged = true;
	}

	if (OldElements.SwitchCapture != NewElements.SwitchCapture)
		Event.SwitchCaptureChanged = true;
	
	if (OldElements.SwitchPlayback != NewElements.SwitchPlayback)
		Event.SwitchPlaybackChanged = true;
}
