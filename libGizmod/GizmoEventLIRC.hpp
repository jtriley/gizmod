    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoEventLIRC.hpp
*** \brief GizmoEventLIRC class header
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

#ifndef __GizmoEventLIRC_h
#define __GizmoEventLIRC_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "GizmoEvent.hpp"
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace Gizmod {

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmoEventLIRC
 * \brief Class for LIRC events
 *
 * This class is for all GizmoEventLIRCs attached to the system.
 */
class GizmoEventLIRC : public GizmoEvent {
public:
	// public variables
	std::string 			Code;				///< Event Code
	int				Repeat;				///< Repeat count of the event
	std::string			Button;				///< Button text from lircd.conf
	std::string			Remote;				///< Name of the remote that triggered the event
	
	// public functions
	
	// static public functions
	static void			buildEventsVectorFromBuffer(std::vector< boost::shared_ptr<GizmoEventLIRC> > & EventVector, H::DynamicBuffer<char> const & Buffer); ///< Build an event list from a read buffer
	
	// construction / deconstruction
	GizmoEventLIRC();						///< Default Constructor
	GizmoEventLIRC(std::string code, int repeat, std::string button, std::string remote, bool IsRemote = false); ///< Init Constructor
	virtual ~GizmoEventLIRC();					///< Destructor

protected:
	
private:
	// private functions
	
	// private member variables
	
	// static private functions
	
private: 
	// serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<GizmoEvent>(*this);
		ar & Code;
		ar & Repeat;
		ar & Button;
		ar & Remote;
	}		
};

//////////////////////////////////////////////////////////////////////////////

} // Gizmod namespace

#endif // __GizmoEventLIRC_h
