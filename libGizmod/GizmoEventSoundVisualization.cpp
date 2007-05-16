    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventSoundVisualization.cpp
*** \brief GizmoEventSoundVisualization class body
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

#include "GizmoEventSoundVisualization.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoEventSoundVisualization Default Constructor
 */
GizmoEventSoundVisualization::GizmoEventSoundVisualization() : GizmoEvent(GIZMO_EVENTCLASS_SOUNDVISUALIZATION, false) {
	mVULeft = mVURight = mVUCombined = 0;
	mType = SOUNDVISUALIZATION_RENDER;
}

/**
 * \brief GizmoEventSoundVisualization Init Constructor
 */
GizmoEventSoundVisualization::GizmoEventSoundVisualization(float VULeft, float VURight, float VUCombined, bool IsRemote) : GizmoEvent(GIZMO_EVENTCLASS_SOUNDVISUALIZATION, IsRemote) {
	mVULeft = VULeft;
	mVURight = VURight;
	mVUCombined = VUCombined;
	mType = SOUNDVISUALIZATION_RENDER;
}

/**
 * \brief GizmoEventSoundVisualization Init Constructor
 */
GizmoEventSoundVisualization::GizmoEventSoundVisualization(SoundVisualizationEventType Type, bool IsRemote) : GizmoEvent(GIZMO_EVENTCLASS_SOUNDVISUALIZATION, IsRemote) {
	mVULeft = mVURight = mVUCombined = 0;
	mType = Type;
}

/**
 * \brief GizmoEventSoundVisualization Destructor
 */
GizmoEventSoundVisualization::~GizmoEventSoundVisualization() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get VU data for the left channel
 * \return The VU data
 */
float GizmoEventSoundVisualization::getVULeft() {
	return mVULeft;
}

/**
 * \brief  Get VU data for the right channel
 * \return The VU data
 */
float GizmoEventSoundVisualization::getVURight() {
	return mVURight;
}

/**
 * \brief  Get VU data for both channels
 * \return The VU data
 */
float GizmoEventSoundVisualization::getVUCombined() {
	return mVUCombined;
}

/**
 * \brief  Get VU data for both channels
 * \return The VU data
 */
SoundVisualizationEventType GizmoEventSoundVisualization::getType() {
	return mType;
}
