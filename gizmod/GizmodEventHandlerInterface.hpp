    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmodEventHandlerInterface.hpp
*** \brief GizmodEventHandlerInterface class header file
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

#ifndef __GizmodEventHandlerInterface_h
#define __GizmodEventHandlerInterface_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <boost/python.hpp>

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class GizmodEventHandlerInterface
 * \brief Main GizmodEventHandlerInterface class
 */
class GizmodEventHandlerInterface : public boost::noncopyable {
public:
	/**
	 * \brief  Faked constructor for the Python object
	 *
	 * Use this as the Object's constructor rather than __init__
	 * 
	 * This is to work around oddities that happen when constructing
	 * a Python object that uses a C++ class as its base
	 */
	virtual void			__construct__() = 0;
	
	/**
	 * \brief  Get whether or not the object has been initialized
	 * \return (bool) True if initialized
	 */
	virtual bool			getInitialized() = 0;
	
	/**
	 * \brief  Script initialization code 
	 *
	 * This python function gets called by GizmoDeamon and is intended to allow for
	 * user specific initialization code to be executed during program startup.
	 * 
	 * It is defined in Gizmod.py in class GizmodDispatcher that inherits from GizmodEventHandler
	 */
	virtual void			initialize() = 0; 	///< Initialization that gets called inside python to init python stuff
		
	// construction / deconstruction
	GizmodEventHandlerInterface();
	virtual ~GizmodEventHandlerInterface();

private:
};

#endif // __GizmodEventHandlerInterface_h
