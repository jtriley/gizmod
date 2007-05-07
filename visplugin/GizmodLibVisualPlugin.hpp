    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodLibVisualPlugin.hpp
*** \brief GizmodLibVisualPlugin class header
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

#ifndef __GizmodLibVisualPlugin_h
#define __GizmodLibVisualPlugin_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmodLibVisualPlugin
 * \brief Helper functions for the Gizmos
 */
class GizmodLibVisualPlugin {
public:
	// public functions
	void				init();				///< Initialize the plugin
	
	// construction / deconstruction 
	GizmodLibVisualPlugin();					///< Default Constructor
	virtual ~GizmodLibVisualPlugin();				///< Destructor
	
private:
	// private functions
};

#endif // __GizmodLibVisualPlugin_h
