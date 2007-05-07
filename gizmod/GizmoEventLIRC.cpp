    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventLIRC.cpp
*** \brief GizmoEventLIRC class body
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

#include "GizmoEventLIRC.hpp"
#include "GizmoLinuxInputDevice.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/Util.hpp"
#include "../libH/stringconverter.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>

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
 * \brief GizmoEventLIRC Default Constructor
 */
GizmoEventLIRC::GizmoEventLIRC() : GizmoEvent(GIZMO_EVENTCLASS_LIRC) {
	Repeat = 0;
}

/**
 * \brief GizmoEventLIRC Init Constructor
 */
GizmoEventLIRC::GizmoEventLIRC(std::string code, int repeat, std::string button, std::string remote) : GizmoEvent(GIZMO_EVENTCLASS_LIRC) {
	Code = code;
	Repeat = repeat;
	Button = button;
	Remote = remote;
}

/**
 * \brief GizmoEventLIRC Destructor
 */
GizmoEventLIRC::~GizmoEventLIRC() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Build an event vector from a read buffer
 * \param  EventVector Reference to a vector which will contain the results
 * \param  Buffer The bufer to convert into events
 */
void GizmoEventLIRC::buildEventsVectorFromBuffer(std::vector< boost::shared_ptr<GizmoEventLIRC> > & EventVector, H::DynamicBuffer<char> const & Buffer) {
	// create some data structures for parsing the info
	typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
	char_separator<char> Separators(" ");
	string Code;
	int Repeat;
	string Button;
	string Remote;
	
	string LIRCData(Buffer.getBuffer(), Buffer.length());
	replace_all(LIRCData, "\n", "");
	tokenizer tok(LIRCData, Separators);
	int count = 0;
	for(tokenizer::iterator iter = tok.begin(); iter!= tok.end(); iter ++, count ++) {
		switch (count) {
		case 0:
			// get the code
			Code = *iter;
			break;
		case 1:
			// get the repeats
			try {
				Repeat = lexical_cast<int>(*iter);
			} catch (bad_lexical_cast const & e) {
				cdbg1 << "Bad LIRC Data Packet <Repeat> [" << LIRCData << "]" << endl;
				return;
			}
			break;
		case 2:
			// get the button
			Button = *iter;
			break;
		case 3:
			// get the button
			Remote = *iter;
			EventVector.push_back(boost::shared_ptr<GizmoEventLIRC>(new GizmoEventLIRC(Code, Repeat, Button, Remote)));
			count = 0;
			break;
		}
	}
}
