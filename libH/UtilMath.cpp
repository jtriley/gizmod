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
 * \brief Default Constructor
**/
UtilMath::UtilMath() {
}

/**
 * \brief Destructor
**/
UtilMath::~UtilMath() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief integer divide and round up
 * \return calculation result
**/
int UtilMath::intDivRoundUp(int Div1, int Div2) {
	return (int) ceil((double)Div1/(double)Div2);
}

/**
 * \brief get a random floating point number
 * \return random float
**/
float UtilMath::random() {
	return rand() / (float) RAND_MAX;
}

/**
 * \brief randomize
 * \return seed the random number generator
**/
void UtilMath::randomize() {
	srand((unsigned)time(NULL));
}

/**
 * \brief get a random floating point number with min and max
 * \return random float
**/
float UtilMath::randomFloat(float MinVal, float MaxVal) {
	float Rnd = random();
	float Range = MaxVal - MinVal;
	float Ans = Range * Rnd;

	return Ans + MinVal;
}

/**
 * \brief get a random integer with min and max
 * \return random int
**/
int UtilMath::randomInt(int MinVal, int MaxVal) {
	float Rnd = random();
	float Range = MaxVal - MinVal;
	float Ans = Range * Rnd;

	return (int) (Ans + MinVal);
}
