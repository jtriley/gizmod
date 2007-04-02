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

////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
template <class DataType>
DynamicBuffer<DataType>::DynamicBuffer() {
	mLength = 0;
	mBuffer = NULL;
}

/**
 * \brief Destructor
 */
template <class DataType>
DynamicBuffer<DataType>::~DynamicBuffer() {
	if (mBuffer)
		free(mBuffer);
	mBuffer = NULL;
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Add data to the buffer
 * \param DataType* Pointer to the data to be added
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
 * \brief  Get the buffer
 * \return The buffer itself
 */
template <class DataType>
const DataType * DynamicBuffer<DataType>::getBuffer() {
	return mBuffer;
}

/**
 * \brief  Get the buffer length
 * \return Length
 */
template <class DataType>
size_t DynamicBuffer<DataType>::getBufferLength() {
	return mLength;
}

//////////////////////////////////////////////////////////////////////////////

} // end namespace
