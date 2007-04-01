  //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// DynamicBuffer.cpp
//
//	DynamicBuffer class
//
///////////////////////////////////////
  ///////////////////////////////////////
  
/*

Copyright (c) 2005, Tim Burrell
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
