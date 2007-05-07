    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoUtils.cpp
*** \brief GizmoUtils class body
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

#include "GizmoUtils.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <bitset>

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoUtils Default Constructor
 */
GizmoUtils::GizmoUtils() {
}

/**
 * \brief GizmoUtils Destructor
 */
GizmoUtils::~GizmoUtils() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Calculate how many bits differ in two bitstrings
 * \param  ReferenceCode The reference code to test against
 * \param  ActualCode The actual received code
 * \return Number of differing bits
 */
int GizmoUtils::bitDifference(unsigned char ReferenceCode, unsigned char ActualCode) {
	unsigned char DifferingBits = ReferenceCode ^ ActualCode;
	bitset<sizeof(unsigned char) * 8> bits(DifferingBits);
	return bits.count();
}
