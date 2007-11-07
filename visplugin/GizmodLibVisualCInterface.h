    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodLibVisualCInterface.h
*** \brief GizmodLibVisualCInterface header
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

#ifndef __GizmodLibVisualCInterface_h
#define __GizmodLibVisualCInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// C interface
///////////////////////////////////////

/**
 * \brief  Clean up
**/
void GizmodLibVisual_CleanUp();

/**
 * \brief  Initialize
**/
void GizmodLibVisual_Init();

/**
 * \brief  Render
**/
void GizmodLibVisual_Render(float VULeft, float VURight, float VUCombined);

#endif // __GizmodLibVisualCInterface_h
