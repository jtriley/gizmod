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

#include "stringconverter.hpp"
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string/case_conv.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
stringconverter::stringconverter(int Value) {
	stringstream ss;
	ss << Value;
	ss >> *this;
}

/**
 * \brief Destructor
 */
stringconverter::~stringconverter() throw() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Convert a string to lower case
 * \param  convertee string to be converted
 */
std::string stringconverter::toLower(std::string const & convertee) {
	string t = convertee;
	boost::to_lower(t);
	return t;
}

/**
 * \brief  Convert a string to upper case
 * \param  convertee string to be converted
 */
std::string stringconverter::toUpper(std::string const & convertee) {
	string t = convertee;
	boost::to_upper(t);
	return t;
}
