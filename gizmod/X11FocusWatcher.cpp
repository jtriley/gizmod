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

#include "X11FocusWatcher.hpp"
#include "../libH/Debug.hpp"
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>

using namespace std;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Callbacks
///////////////////////////////////////

int X11FocusWatcher::x11ErrorHandler(Display * display, XErrorEvent * error) {
	// do nothing we don't care
	return 0;
}

int X11FocusWatcher::x11IOErrorHandler(Display * display) {
	// do nothing we don't care
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

X11FocusWatcher::X11FocusWatcher() {
	m_Display = NULL;
	m_WatchingDevice = false;
}

X11FocusWatcher::~X11FocusWatcher() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

bool X11FocusWatcher::checkEventsWaiting() {
	//Debug::outDebug("X11FocusWatcher :: Watching Device Events...");
	
	m_WatchingDevice = true;
	static std::string LastWin;
	std::string WinName;
	getForegroundWindowProperties(&WinName);
	if (WinName == LastWin)
		return false;

	// window changed! notify
	//onForegroundWindowChange(WinName);
	LastWin = WinName;
	
	return true;
}

void X11FocusWatcher::closeDisplay() {
 	if (!m_Display)
		return;

	XCloseDisplay(m_Display);
	m_Display = NULL;

	cdbg << "X11FocusWatcher :: Display Closed" << endl;
}

std::string X11FocusWatcher::getDeviceName() {
	return "X11FocusWatcher";
}

bool X11FocusWatcher::getForegroundWindowProperties(std::string * WindowName) {
 	if (!m_Display) {
		*WindowName = "(not connected to X11)";
		return false;
	}

	Window 		window;
	int		revert_to_return;

	XGetInputFocus(m_Display, &window, &revert_to_return);
	*WindowName = getWindowName(window);

	//Debug::outDebug("X11FocusWatcher :: Active Window = [0x%lx] [%s]", window, WindowName->getString());

	return true;
}

/*
 * Routine to display a window id in dec/hex with name if window has one
 * Taken from xwininfo.c from xorg source, thanks xorg guys you rule!
 *
 * I modified it to correctly get the parent window if necessary
 */
 
std::string X11FocusWatcher::getWindowName(Window window, bool recurse) {
	XTextProperty tp;
	Display * dpy = m_Display;
	
	if (!window) {
		return "";
	} else {
		if (window == RootWindow(dpy, XDefaultScreen(dpy))) {
			return "(root window)";
	}
#ifdef NO_I18N
	char * win_name;
	if (!XFetchName(dpy, window, &win_name)) { /* Get window name if any */
		XFree(win_name);
		Window root_ret, parent_ret;
		unsigned int nChildren;
		Window * children;
		XQueryTree(dpy, window, &root_ret, &parent_ret, &children, &nChildren);
		XFree(children);
		if ((XGetWMName(dpy, parent_ret, &tp)) && (recurse)) {
			XFree((void*)tp.value);
			return getWindowName(parent_ret, false);
		} else {
			if (tp.value)
				XFree((void*)tp.value);
			return "(no name)";
		}
	} else if (win_name) {
		const std::string retStr = win_name;
		XFree(win_name);
		return retStr;
	}
#else
	if (!XGetWMName(dpy, window, &tp)) { // Get window name if any
		if (tp.value)
			XFree((void*)tp.value);
		Window root_ret, parent_ret;
		unsigned int nChildren;
		Window * children;
		XQueryTree(dpy, window, &root_ret, &parent_ret, &children, &nChildren);
		/* causes seg faults!
		if ( (children) && (nChildren > 0) )
			XFree(children);
		*/
		if ((XGetWMName(dpy, parent_ret, &tp)) && (recurse)) {
			XFree((void*)tp.value);
			return getWindowName(parent_ret, false);
		} else {
			if (tp.value)
				XFree((void*)tp.value);
			return "(no name)";
		}
	} else if (tp.nitems > 0) {
		std::string retStr;
		int count = 0, i, ret;
		char **list = NULL;
		ret = XmbTextPropertyToTextList(dpy, &tp, &list, &count);
		if((ret == Success || ret > 0) && list != NULL) {
			for(i=0; i<count; i++)
				retStr += (const char *) list[i];
			XFree((void*)tp.value);
			XFreeStringList(list);
			return retStr;
		} else {
			XFree((void*)tp.value);
			if (list)
				XFreeStringList(list);
			retStr = (const char *) tp.value;
			return retStr;
		}
	}
#endif
	else
		return "(no name)";
	}
	
	return "(unknown)";
}

bool X11FocusWatcher::init() {
	if (!openDisplay(m_DisplayName)) {
		cdbg << "X11FocusWatcher :: Failed to Open X11 Display [" << m_DisplayName << "]!" << endl;
		return false;
	}
	
	Window window;
	int revert_to_return;
	string WindowName;
	while (1) {
		XGetInputFocus(m_Display, &window, &revert_to_return);
		XSelectInput(m_Display, window, FocusChangeMask);
		WindowName = getWindowName(window);
		
		XEvent event;
		XNextEvent(m_Display, &event);
		switch (event.type) {
		case FocusIn:
			cout << "Current Focus: " << WindowName << endl;
			break;
		case FocusOut:
			cout << "Leaving Focus: " << WindowName << endl;
			break;
		default:
			cdbg << "Unkown Event Type: " << event.type << endl;		
			break;
		}
	}

	cdbg << "X11FocusWatcher :: X11 Input Plugin Initialized." << endl;
	return true;
}

bool X11FocusWatcher::openDisplay(std::string DisplayName) {
	if (m_Display)
		closeDisplay();

	if (DisplayName == "")
		m_DisplayName = XDisplayName(NULL);
	else
		m_DisplayName = DisplayName;


	if ( (m_Display = XOpenDisplay(m_DisplayName.c_str())) == NULL ) {
		cdbg << "X11FocusWatcher :: Unable to Open Display [" << m_DisplayName << "]" << endl;
		return false;
	}

	// set the error handlers
	// special thanks to ajax from #xorg for this tip
	// you have no idea how annoying this was to track down
	XSetErrorHandler(x11ErrorHandler);
	XSetIOErrorHandler(x11IOErrorHandler);

	m_Screen = DefaultScreen(m_Display);
	m_RootWindow = RootWindow(m_Display, m_Screen);

	cdbg << "X11FocusWatcher :: Display Opened [" << m_DisplayName << "]" << endl;
	
	return true;
}

void X11FocusWatcher::shutdown() {
	cdbg << "X11FocusWatcher :: Shutting Down..." << endl;
	m_WatchingDevice = false;
	closeDisplay();
}
