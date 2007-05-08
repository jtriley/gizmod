    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaMixerElements.hpp
*** \brief AlsaMixerElements header
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

#ifndef __AlsaMixerElements_h
#define __AlsaMixerElements_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "AlsaSoundCardInterface.hpp"
#include "AlsaEvent.hpp"

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// AlsaMixerElements Class Definition
///////////////////////////////////////

/**
 * \class  AlsaMixerElements
 * \brief  Data structure that holds information about each Mixer element
 */
class AlsaMixerElements {
public:	
	// public member variables
	bool				IsActive;			///< Is the mixer element currently active
	bool				HasCommonVolume;		///< Does the mixer element have a common playback volume
	bool				HasPlaybackVolume;		///< Does the mixer element have a playback volume
	bool				HasPlaybackVolumeJoined;	///< Does the mixer element have a joined playback volume
	bool				HasCaptureVolume;		///< Does the mixer element have a capture volume
	bool				HasCaptureVolumeJoined;		///< Does the mixer element have a joined capture volume
	bool				HasCommonSwitch;		///< Does the mixer element have a common switch
	bool				HasPlaybackSwitch;		///< Does the mixer element have a playback switch 
	bool				HasPlaybackSwitchJoined;	///< Does the mixer element have a joined playback switch 
	bool				HasCaptureSwitch;		///< Does the mixer element have a capture switch 
	bool				HasCaptureSwitchJoined;		///< Does the mixer element have a joined capture switch 
	bool				HasCaptureSwitchExclusive;	///< Does the mixer element have an exclusive capture switch 
	
	long				VolumePlayback;			///< Playback volume
	long				VolumePlaybackMin;		///< Min playback volume
	long				VolumePlaybackMax;		///< Max playback volume
	float				VolumePlaybackPercent;		///< Percent playback volume
	
	long				VolumeCapture;			///< Capture volume
	long				VolumeCaptureMin;		///< Min Capture volume
	long				VolumeCaptureMax;		///< Max Capture volume
	float				VolumeCapturePercent;		///< Percent Capture volume
	
	bool				SwitchPlayback;			///< Value of the playback switch
	bool				SwitchCapture;			///< Value of the capture switch
	
	// construction / deconstruction
	AlsaMixerElements();
	AlsaMixerElements(AlsaMixerElements const & Init);
	virtual ~AlsaMixerElements();
	
	// static public functions
	void				buildEventFromMixerStates(AlsaEvent & Event, AlsaMixerElements const & OldElements, AlsaMixerElements const & NewElements); ///< Build an event from two mixer states
	
private:
	// private functions
		
	// private member variables
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & IsActive;
		ar & HasCommonVolume;
		ar & HasPlaybackVolume;
		ar & HasPlaybackVolumeJoined;
		ar & HasCaptureVolume;
		ar & HasCaptureVolumeJoined;
		ar & HasCommonSwitch;
		ar & HasPlaybackSwitch;
		ar & HasPlaybackSwitchJoined;
		ar & HasCaptureSwitch;
		ar & HasCaptureSwitchJoined;
		ar & HasCaptureSwitchExclusive;
		ar & VolumePlayback;
		ar & VolumePlaybackMin;
		ar & VolumePlaybackMax;
		ar & VolumePlaybackPercent;
		ar & VolumeCapture;
		ar & VolumeCaptureMin;
		ar & VolumeCaptureMax;
		ar & VolumeCapturePercent;
		ar & SwitchPlayback;
		ar & SwitchCapture;
	}				
};

#endif // __AlsaMixerElements_h
