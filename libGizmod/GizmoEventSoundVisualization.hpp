    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventSoundVisualization.hpp
*** \brief GizmoEventSoundVisualization class header
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

#ifndef __GizmoEventSoundVisualization_h
#define __GizmoEventSoundVisualization_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEvent.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

/**
 * \enum   SoundVisualizationEventType
 * \brief  Type of the SoundVisualization event
 */
typedef enum {
	SOUNDVISUALIZATION_CONNECT,
	SOUNDVISUALIZATION_DISCONNECT,
	SOUNDVISUALIZATION_RENDER
} SoundVisualizationEventType;
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEventSoundVisualization
 * \brief Class for CPU events
 *
 * This class is for all GizmoEventSoundVisualizations attached to the system.
 */
class GizmoEventSoundVisualization : public GizmoEvent {
public:
	// public member variables
	float				getVULeft();				///< Get VU data for the left channel
	float				getVURight();				///< Get VU data for the rightchannel
	float				getVUCombined();			///< Get VU data for combined channels
	SoundVisualizationEventType	getType();				///< Get the event type
	
	// public functions
	
	// construction / deconstruction
	GizmoEventSoundVisualization(); 					///< Default Constructor
	GizmoEventSoundVisualization(SoundVisualizationEventType Type, bool IsRemote = false); ///< Init Constructor
	GizmoEventSoundVisualization(float vuLeft, float vuRight, float vuCombined, bool IsRemote = false); ///< Init Constructor
	virtual ~GizmoEventSoundVisualization();				///< Destructor

private:
	// private functions
	
	// private member variables
	float				mVULeft;				///< VU data for the left channel
	float				mVURight;				///< VU data for the right channel
	float				mVUCombined;				///< VU data for the two channels combined
	SoundVisualizationEventType	mType;					///< The event type
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<GizmoEvent>(*this);
		ar & mVULeft;
		ar & mVURight;
		ar & mVUCombined;
		ar & mType;
	}	
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __GizmoEventSoundVisualization_h
