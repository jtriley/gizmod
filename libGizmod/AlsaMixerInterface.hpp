    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaMixerInterface.hpp
*** \brief AlsaMixerInterfaceheader
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

#ifndef __AlsaMixerInterface_h
#define __AlsaMixerInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "AlsaInterface.hpp"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// AlsaMixerInterface Class Definition
///////////////////////////////////////

/**
 * \class  AlsaMixerInterface
 * \brief  Data structure that holds information about Alsa events
**/
class AlsaMixerInterface {
public:	
	// public member variables
	
	// public functions
	virtual int 			signalMixerEvent() = 0;		///< Signal a manual mixer event

	// construction / deconstruction
	AlsaMixerInterface();
	virtual ~AlsaMixerInterface();
	
protected:
	// protected member variables

private:
	// private functions
		
	// private member variables
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __AlsaMixerInterface_h
