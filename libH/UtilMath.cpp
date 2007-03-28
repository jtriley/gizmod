    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  UtilMath.cpp
*** \brief UtilMath class body
***
*****************************************
  *****************************************
    **/
    
/*

Copyright (c) 2007, Tim Burrell
All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "UtilMath.hpp"
#include "../libH/Debug.hpp"
#include <sys/time.h>
#include <math.h>

using namespace H;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * Constructor
 */
UtilMath::UtilMath() {
}

/**
 * Destructor
 */
UtilMath::~UtilMath() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief integer divide and round up
 * \return calculation result
 */
int UtilMath::intDivRoundUp(int Div1, int Div2) {
	return (int) ceil((double)Div1/(double)Div2);
}

/**
 * \brief get a random floating point number
 * \return random float
 */
float UtilMath::random() {
	return rand() / (float) RAND_MAX;
}

/**
 * \brief randomize
 * \return seed the random number generator
 */
void UtilMath::randomize() {
	srand((unsigned)time(NULL));
}

/**
 * \brief get a random floating point number with min and max
 * \return random float
 */
float UtilMath::randomFloat(float MinVal, float MaxVal) {
	float Rnd = random();
	float Range = MaxVal - MinVal;
	float Ans = Range * Rnd;

	return Ans + MinVal;
}

/**
 * \brief get a random integer with min and max
 * \return random int
 */
int UtilMath::randomInt(int MinVal, int MaxVal) {
	float Rnd = random();
	float Range = MaxVal - MinVal;
	float Ans = Range * Rnd;

	return (int) (Ans + MinVal);
}
