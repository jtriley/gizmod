    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  X11FocusWatcher.hpp
*** \brief X11FocusWatcher header
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

#ifndef __X11FocusWatcher_h
#define __X11FocusWatcher_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

class X11FocusWatcher {
public:
	// public functions
	bool		checkEventsWaiting();
	void		closeDisplay();
	std::string	getDeviceName();
	bool 		getForegroundWindowProperties(std::string * WindowName);
	std::string	getWindowName(Window window, bool recurse = true);
	bool		init();
	bool 		openDisplay(std::string DisplayName);
	void 		shutdown();

	// construction / deconstruction
	X11FocusWatcher();
	virtual ~X11FocusWatcher();
	
	// public static functions
	static int	x11ErrorHandler(Display * display, XErrorEvent * error);
	static int	x11IOErrorHandler(Display * display);

private:
	// private member variables
	Display	*	m_Display;
	std::string	m_DisplayName;
	Window		m_RootWindow;
	int		m_Screen;
	bool		m_WatchingDevice;
};

#endif // __X11FocusWatcher_h
