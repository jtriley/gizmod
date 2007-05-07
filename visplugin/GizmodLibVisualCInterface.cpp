    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodLibVisualCInterface.cpp
*** \brief GizmodLibVisualCInterface class body
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

#include "GizmodLibVisualPlugin.hpp"

/////////////////////////////////////////////////////////////////////////////
// C interface
///////////////////////////////////////

/**
 * The Plugin Object
 */
GizmodLibVisualPlugin Plugin;

extern "C" {

/**
 * \brief  Initialize
 */
void GizmodLibVisual_Init() {
	Plugin.init();
}

/**
 * \brief  Clean up
 */
void GizmodLibVisual_CleanUp() {
	Plugin.shutdown();
}

/** 
 * \brief  Render the audio data
 * \param  PCMData The audio data
 */
void GizmodLibVisual_Render(float VULeft, float VURight, float VUCombined) {
	Plugin.render(VULeft, VURight, VUCombined);
}

}

