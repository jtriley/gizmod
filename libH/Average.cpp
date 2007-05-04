    /**   
  *********************************************************************
*************************************************************************
*** 
*** \file  Average.cpp
*** \brief Average class body file
***
*****************************************
  *****************************************
    **/

/*
  
  Copyright (c) 2007, Tim Burrell
  Initial version Copyright (c) 2005, Alexander Kroeller
  
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

#include "Average.hpp"

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

using namespace std;
using namespace H;

//////////////////////////////////////////////////////////////////////////////
// Typedefs, enums, etc
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief  Default Constructor
 */
Average::Average(int Size) {
	mValues.resize(Size);
	mHeadIdx = 0;
	mSum = 0.0;
	mFillState = 0;
}

/**
 * \brief  Destructor
 */
Average::~Average() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Push a value to be averaged
 * \param  Value The value
 */
void Average::push(double Value) {
	if (mFillState == mValues.size()) {
		mSum += Value - mValues[mHeadIdx];
		mValues[mHeadIdx] = Value;
	} else {
		++ mFillState;
		mSum += Value;
		mValues[mHeadIdx] = Value;
	}
	mHeadIdx = (mHeadIdx + 1) % mValues.size();
}

/**
 * \brief  Get the average
 * \return The average of all pushed values
 */
double Average::average(void) {
   if (mFillState == 0)
      return 0.0;
   else
      return mSum / double(mFillState);
}
