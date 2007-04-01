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

Copyright (c) 2006, Tim Burrell
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

#ifndef __DynamicBuffer_h
#define __DynamicBuffer_h

#if HAVE_CONFIG_H
#include "config.h"
#endif


//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedefs, enums, etc
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Class Definition
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
	const DataType * 	getBuffer();			///< Get the buffer
	size_t			getBufferLength();		///< Get the buffer length

	// construction / deconstruction
	DynamicBuffer();					///< Default Constructor
	virtual ~DynamicBuffer();				///< Destructor
	
private:
	// private member variables
	size_t			mLength;			///< Length of the buffer
	DataType *		mBuffer;			///< The buffer itself
};

//////////////////////////////////////////////////////////////////////////////

} // end namespace

#include "DynamicBuffer.cpp"

//////////////////////////////////////////////////////////////////////////////

#endif // __DynamicBuffer_h
