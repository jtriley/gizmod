    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  stringconverter.cpp
*** \brief stringconverter class body
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

#ifndef __stringconverter_h
#define __stringconverter_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class stringconverter
 * \brief Generic stringconverter class
 *
 * Converts various datatypes to string
 */
class stringconverter : public std::string {
public:	
	stringconverter(int Value);
	virtual ~stringconverter() throw() ;
};

//////////////////////////////////////////////////////////////////////////////

}

#endif // __stringconverter_h
