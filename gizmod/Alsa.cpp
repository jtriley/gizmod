    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Alsa.cpp
*** \brief Alsa Class Body
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

#include "Alsa.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/format.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  Alsa Default Constructor
 */
Alsa::Alsa() {
}

/**
 * \brief  Alsa Destructor
 */
Alsa::~Alsa() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Initialize ALSA
 */
void Alsa::init() {
	// first make sure the connections are closed
	shutdown();
	
	// initialize
	int ret = -1, CardID;
	do {
		// get the next sound card
		if ((CardID = snd_card_next(&ret)) < 0) {
			cerr << "Failed to Query Sound Card [" << ret + 1 << "] -- Error Code: " << CardID;
			continue;
		}
		if (ret > -1) {
			shared_ptr<AlsaSoundCard> pSoundCard = shared_ptr<AlsaSoundCard>(new AlsaSoundCard(CardID));
			mSoundCards.push_back(pSoundCard);		
		}
	} while (ret != -1);
}

/**
 * \brief Shutdown the ALSA connection
 */
void Alsa::shutdown() {
	if (mSoundCards.size())
		cdbg1 << "Shutting down [" << mSoundCards.size() << "] sound card connections..." << endl;
	mSoundCards.clear();
}
