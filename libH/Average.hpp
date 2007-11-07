    /**   
  *********************************************************************
*************************************************************************
*** 
*** \file  Average.hpp
*** \brief Average class header file
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

#ifndef __Average_h
#define __Average_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

/**
 * \namespace H
 * \brief     H namespace
 *
 * All code in the H namespace gets its inspiration from the best movie ever made:
 *    Hackers
**/
namespace H {

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Average
 * \brief Class for averaging things out over a number of iterations
**/
class Average {
public:
	// public functions
	void  				push(double Value);		///< Push a value
	double 				average();			///< Get the average
	
	// construct / deconstruction
	Average(int Size = 10);						///< Init constructor
	virtual ~Average();						///< Destructor

private:
	// private member variables
   	std::vector<double>		mValues;			///< Averaged values
   	size_t     			mHeadIdx;			///< Current location in the circular buffer
   	double  			mSum;				///< Sum of the Average
   	size_t				mFillState;			///< Current fill state
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __Average_h

