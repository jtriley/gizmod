    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  AlsaSoundCardInterface.cpp
*** \brief AlsaSoundCardInterface Class Body
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

#include "AlsaSoundCardInterface.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"

using namespace std;
using namespace H;
using namespace Gizmod;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  AlsaSoundCardInterface Default Constructor
**/
AlsaSoundCardInterface::AlsaSoundCardInterface(AlsaInterface * piAlsa) {
	mpiAlsa = piAlsa;
}

/**
 * \brief  AlsaSoundCardInterface Destructor
**/
AlsaSoundCardInterface::~AlsaSoundCardInterface() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Add a mixer to the manual update list
 * \param  pMixer The mixer to add
**/
void AlsaSoundCardInterface::addManualUpdater(AlsaMixerInterface * pMixer) {
	// make sure it's not already in the list
	for (list<AlsaMixerInterface *>::iterator iter = mUpdateList.begin(); iter != mUpdateList.end(); iter ++)
		if (*iter == pMixer)
			return;
	
	mUpdateList.push_back(pMixer);
}

/**
 * \brief  Get a pointer to the Alsa intantiation
 * \return Point to the AlsaInterface
**/
AlsaInterface * AlsaSoundCardInterface::getAlsa() {
	return mpiAlsa;
}
