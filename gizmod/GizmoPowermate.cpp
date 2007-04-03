    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoPowermate.cpp
*** \brief GizmoPowermate class body
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

#include "GizmoPowermate.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def   GIZMOPOWERMATE_TYPE
 * \brief String type of this gizmo
 */
#define GIZMOPOWERMATE_TYPE	"Powermate"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoPowermate Default Constructor
 */
GizmoPowermate::GizmoPowermate() {
}

/**
 * \brief GizmoPowermate Destructor
 */
GizmoPowermate::~GizmoPowermate() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Get the Powermate's LED Value
 * \return LED value (0-255)
 */
unsigned char GizmoPowermate::getLEDValue() {
	return 0;
}

/**
 * \brief  Get the type of this Gizmo
 * \return Type of the Gizmo
 */
std::string GizmoPowermate::getType() {
	return GIZMOPOWERMATE_TYPE;
}
