    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  PythonEmbedder.cpp
*** \brief PythonEmbedder class body
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

#include "PythonEmbedder.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/python.hpp>

using namespace std;
using namespace boost;
using namespace boost::python;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs / defines
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
PythonEmbedder::PythonEmbedder() {
}

/**
 * \brief Default Destructor
 */
PythonEmbedder::~PythonEmbedder() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Initialize the Python Interpreter
 */
void PythonEmbedder::initialize() {
	cdbg << "Embedding Python Interpreter..." << endl;
	Py_Initialize();
}
