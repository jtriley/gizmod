    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  DynamicBuffer.cpp
*** \brief DynamicBuffer class body
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

#include "Debug.hpp"
#include "Exception.hpp"
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief DynamicBuffer Default Constructor
 */
template <class DataType>
DynamicBuffer<DataType>::DynamicBuffer() {
	mLength = 0;
	mBuffer = NULL;
}

/**
 * \brief DynamicBuffer Destructor
 */
template <class DataType>
DynamicBuffer<DataType>::~DynamicBuffer() {
	if (mBuffer)
		free(mBuffer);
	mBuffer = NULL;
}

/**
 * \brief DynamicBufferConverter Default Constructor
 */
template <class ConvertTo, class DataType>
DynamicBufferConverter<ConvertTo, DataType>::DynamicBufferConverter() {
}

/**
 * \brief DynamicBufferConverter Destructor
 */
template <class ConvertTo, class DataType>
DynamicBufferConverter<ConvertTo, DataType>::~DynamicBufferConverter() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Add data to the buffer
 * \param AddBuf Pointer to the data to be added
 * \param BufLen Length of data to be added
 */
template <class DataType>
void DynamicBuffer<DataType>::addToBuffer(const DataType * AddBuf, size_t BufLen) {
	if ((mBuffer = (DataType *) (realloc(mBuffer, (mLength + 1 + BufLen) * sizeof(DataType)))) == NULL)
		throw H::Exception("DynamicBuffer :: Failed to Allocate Memory!!", __FILE__, __FUNCTION__, __LINE__);

	memcpy(mBuffer + mLength, AddBuf, sizeof(DataType) * BufLen);	
	mLength += BufLen;
	mBuffer[mLength] = '\0';
}

/**
 * \brief Convert Buffer to a vector objects contained in the buffer
 * \param ConvertedVector Result of the conversion
 * \param Buffer Buffer to convert data from 
 */
template <class DataType, class ConvertTo>
void DynamicBufferConverter<DataType, ConvertTo>::convert(std::vector<ConvertTo> & ConvertedVector, DynamicBuffer<DataType> const & Buffer) {
	int NumItems = Buffer.length() / sizeof(ConvertTo);
	ConvertedVector.resize(NumItems);
	const char * tBuf = Buffer.getBuffer();
	for (int lp = 0; lp < NumItems; lp ++)
		memcpy(&ConvertedVector[lp], tBuf + (lp * sizeof(ConvertTo)), sizeof(ConvertTo));
}

/**
 * \brief  Get the buffer
 * \return The buffer itself
 */
template <class DataType>
const DataType * DynamicBuffer<DataType>::getBuffer() const {
	return mBuffer;
}

/**
 * \brief  Get the buffer length
 * \return Length
 */
template <class DataType>
size_t DynamicBuffer<DataType>::length() const {
	return mLength;
}

//////////////////////////////////////////////////////////////////////////////

} // end namespace
