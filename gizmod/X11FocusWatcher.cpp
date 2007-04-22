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
#include "../libH/Exception.hpp"
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

/**
 * \brief  Handle X11 errors
 */
int X11FocusWatcher::x11ErrorHandler(Display * display, XErrorEvent * error) {
	// do nothing we don't care
	return 0;
}

/**
 * \brief  Handle X11 IO errors
 */
int X11FocusWatcher::x11IOErrorHandler(Display * display) {
	// do nothing we don't care
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/** 
 * \brief  X11FocusEvent Default Constructor
 */
X11FocusEvent::X11FocusEvent(X11FocusEventType eventType, std::string windowName, std::string windowNameFormal, std::string windowClass) {
	EventType = eventType;
	WindowName = windowName;
	WindowNameFormal = windowNameFormal;
	WindowClass = windowClass;
}

/** 
 * \brief  X11FocusWatcher Default Constructor
 */
X11FocusWatcher::X11FocusWatcher() : mThreadProc(this) {
	mDisplay = NULL;
	mWatching = false;
	init();
}

/**
 * \brief  X11FocusEvent Destructor
 */
X11FocusEvent::~X11FocusEvent() {
}

/**
 * \brief  X11FocusWatcher Destructor
 */
X11FocusWatcher::~X11FocusWatcher() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Close the X11 display
 */
void X11FocusWatcher::closeDisplay() {
 	if (!mDisplay)
		return;

	XCloseDisplay(mDisplay);
	mDisplay = NULL;
}

/**
 * \brief  Create a X11FocusEvent from a Window
 * \param  window The Window to create an event from
 * \return The event
 */
X11FocusEvent X11FocusWatcher::createFocusEvent(Window const & window, X11FocusEventType EventType) {
	XClassHint * pClassHint;
	pClassHint = XAllocClassHint();
	
	if (XGetClassHint(mDisplay, window, pClassHint) == 0)
		throw H::Exception("Failed to create Window Event!", __FILE__, __FUNCTION__, __LINE__);
	
	X11FocusEvent Event = X11FocusEvent(EventType, getWindowName(window), pClassHint->res_name, pClassHint->res_class);
	XFree(pClassHint->res_name);
	XFree(pClassHint->res_class);
	XFree(pClassHint);
	return Event;
}

/**
 * \brief  Get the name of a Window 
 * \param  window The Window itself
 * \param  recure Set to true if we should recurse on this window
 * \return A string that contains the name of the window
 *
 * Routine to display a window id in dec/hex with name if window has one
 * Taken from xwininfo.c from xorg source, thanks xorg guys!
 *
 * Modified to correctly get the parent window if necessary
 */
std::string X11FocusWatcher::getWindowName(Window const & window, bool recurse) {
	XTextProperty tp;
	Display * dpy = mDisplay;
	
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
		if (children) XFree(children);
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
		// FIXME may cause seg faults!
		if (children) XFree(children);
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

/**
 * \brief  Initialize the focus watcher (create a new thread and start watching)
 */
void X11FocusWatcher::init() {
	boost::thread thrd(mThreadProc);
}

/**
 * \brief  Event triggered on a Focus In
 * \param  Event The Focus Event
 */
void X11FocusWatcher::onFocusIn(X11FocusEvent const & Event) {
	// override me
	cdbg << "X11FocusWatcher -- Current Focus: " << Event.WindowName << " [" << Event.WindowNameFormal << "] <" << Event.WindowClass << ">" << endl;
}

/**
 * \brief  Event triggered on a Focus In
 * \param  Event The Focus Event
 */
void X11FocusWatcher::onFocusOut(X11FocusEvent const & Event) {
	// override me
	cdbg << "X11FocusWatcher -- Leaving Focus: " << Event.WindowName << " [" << Event.WindowNameFormal << "] <" << Event.WindowClass << ">" << endl;
}

/** 
 * \brief  Open an X11 Display
 * \param  DisplayName The display to open (ie, "" for default, or ":1" for 1)
 */
bool X11FocusWatcher::openDisplay(std::string DisplayName) {
	if (mDisplay)
		closeDisplay();

	if (DisplayName == "")
		mDisplayName = XDisplayName(NULL);
	else
		mDisplayName = DisplayName;


	if ( (mDisplay = XOpenDisplay(mDisplayName.c_str())) == NULL ) {
		cdbg << "X11FocusWatcher :: Unable to Open Display [" << mDisplayName << "]" << endl;
		return false;
	}

	// set the error handlers
	// special thanks to ajax from #xorg for this tip
	// you have no idea how annoying this was to track down
	XSetErrorHandler(x11ErrorHandler);
	XSetIOErrorHandler(x11IOErrorHandler);
	mScreen = DefaultScreen(mDisplay);
	
	return true;
}

/**
 * \brief  Set all windows to report the FocusChangeMask
 */
void X11FocusWatcher::setFocusEventMask() {
	Window RootRet, ParentRet;
	unsigned int nChildren;
	Window * Children;
	XQueryTree(mDisplay, RootWindow(mDisplay, mScreen), &RootRet, &ParentRet, &Children, &nChildren);
	for (unsigned int lp = 0; lp < nChildren; lp ++)
		XSelectInput(mDisplay, Children[lp], FocusChangeMask);		
	if (Children)
		XFree(Children);
}

/**
 * \brief  Signal the watching thread to shut itself down
 */
void X11FocusWatcher::shutdown() {
	mWatching = false;
}

/** 
 * \brief  The ThreadProc
 *
 * This is where all the magic happens
 */
void X11FocusWatcher::threadProc() {
	if (!openDisplay(mDisplayName)) {
		cdbg << "X11FocusWatcher :: Failed to Open X11 Display [" << mDisplayName << "]!" << endl;
		return;
	}
	
	Window window;
	int revert_to_return;
	string WindowName;
	
	// fire initial event
	XGetInputFocus(mDisplay, &window, &revert_to_return);
	try {
		X11FocusEvent Event = createFocusEvent(window, X11FOCUSEVENT_IN);
		onFocusIn(Event);
	} catch (Exception e) {
		cerr << e.getExceptionMessage() << endl;
	}
	
	// Watch for focus changes	
	mWatching = true;
	while (mWatching) {
		XGetInputFocus(mDisplay, &window, &revert_to_return);
		setFocusEventMask();
		WindowName = getWindowName(window);
		
		XEvent event;
		XNextEvent(mDisplay, &event);
		try {
			switch (event.type) {
			case FocusIn: {
				X11FocusEvent Event = createFocusEvent(window, X11FOCUSEVENT_IN);
				onFocusIn(Event);
				break; }
			case FocusOut: {
				X11FocusEvent Event = createFocusEvent(window, X11FOCUSEVENT_OUT);
				onFocusOut(Event);
				break; }
			default:
				cdbg << "Unkown Event Type: " << event.type << endl;		
				break;
			}
		} catch (Exception e) {
			cerr << e.getExceptionMessage() << endl;
		}
	}

	closeDisplay();
}
