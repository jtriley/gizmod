    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  DynamicBuffer.hpp
*** \brief DynamicBuffer class header
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

#ifndef __DynamicBuffer_h
#define __DynamicBuffer_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedefs, enums, etc
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// DynamicBuffer Class Definition
///////////////////////////////////////

/**
 * \class DynamicBuffer
 * \brief Implementation of a simple, highly efficient, dynamic buffer
 *
 * Nothing in STL can currently be used as a buffer efficiently
 * This uses realloc, and memcpy to be as fast as possible
 */

template <class DataType>
class DynamicBuffer {
public:
	// public functions
	void			addToBuffer(const DataType * AddBuf, size_t BufLen); ///< Add data to the buffer
	const DataType * 	getBuffer() const;		///< Get the buffer
	size_t			length() const;			///< Get the buffer length

	// construction / deconstruction
	DynamicBuffer();					///< Default Constructor
	virtual ~DynamicBuffer();				///< Destructor
	
private:
	// private member variables
	size_t			mLength;			///< Length of the buffer
	DataType *		mBuffer;			///< The buffer itself
};

//////////////////////////////////////////////////////////////////////////////
// DynamicBufferConverter Class Definition
///////////////////////////////////////

/**
 * \class DynamicBufferConverter
 * \brief Convert a Dynamic buffer to an array of structures or classes
 */

template <class DataType, class ConvertTo>
class DynamicBufferConverter {
public:
	// public functions
	static void 		convert(std::vector<ConvertTo> & ConvertedVector, DynamicBuffer<DataType> const & Buffer); ///< Convert Buffer to a vector objects contained in the buffer

	// construction / deconstruction
	DynamicBufferConverter();				///< Default Constructor
	virtual ~DynamicBufferConverter();			///< Destructor
	
private:
	// private member variables
};

//////////////////////////////////////////////////////////////////////////////

} // end namespace

#include "DynamicBuffer.cpp"

//////////////////////////////////////////////////////////////////////////////

#endif // __DynamicBuffer_h
