    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  X11FocusWatcher.cpp
*** \brief X11FocusWatcher Class Body
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
#include "../libH/stringconverter.hpp"
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Typedef's, structs
///////////////////////////////////////

/**
 * \def    WINDOW_UNKNOWN
 * \brief  Default text used to describe an unknown Window (Formal)
 */
#define WINDOW_UNKNOWN		"Unknown"

/**
 * \def    TITLE_UNKNOWN
 * \brief  Default text used to describe an unknown Window (Title)
 */
#define TITLE_UNKNOWN		"(No Name)"

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
X11FocusEvent::X11FocusEvent() {
	EventType = X11FOCUSEVENT_IN;
	WindowName = TITLE_UNKNOWN;
	WindowNameFormal = WINDOW_UNKNOWN;
	WindowClass = WINDOW_UNKNOWN;
}

/** 
 * \brief  X11FocusEvent Init Constructor
 */
X11FocusEvent::X11FocusEvent(X11FocusEventType eventType, std::string windowName, std::string windowNameFormal, std::string windowClass) {
	EventType = eventType;
	WindowName = windowName;
	WindowNameFormal = windowNameFormal;
	WindowClass = windowClass;
}

/** 
 * \brief  X11FocusEvent Init Constructor
 */
X11FocusEvent::X11FocusEvent(X11FocusEvent const & Event) {
	EventType = Event.EventType;
	WindowName = Event.WindowName;
	WindowNameFormal = Event.WindowNameFormal;
	WindowClass = Event.WindowClass;
}

/** 
 * \brief  X11FocusWatcher Default Constructor
 */
X11FocusWatcher::X11FocusWatcher() : mThreadProc(this) {
	mCurrentWindow = -1;
	mDisplay = NULL;
	mWatching = false;
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
	tuple<string, string, string> WindowInfo = getWindowName(mDisplay, window);
	X11FocusEvent Event(EventType, WindowInfo.get<0>(), WindowInfo.get<1>(), WindowInfo.get<2>());
	return Event;
}

/**
 * \brief  Get the name and class hints of a Window 
 * \param  dpy The Display 
 * \param  window The Window itself
 * \param  recurse Set to true if we should recurse on this window
 * \return A string that contains the name of the window
 *
 * Routine to display a window id in dec/hex with name if window has one
 * Taken from xwininfo.c from xorg source, thanks xorg guys!
 *
 * Modified to correctly get the parent window if necessary, as well
 * as window class and formal name information
 */
boost::tuple<std::string, std::string, std::string> X11FocusWatcher::getWindowName(Display * dpy, Window const & window, bool recurse) {
	XTextProperty tp;
	string WindowName = TITLE_UNKNOWN;
	string WindowNameFormal = WINDOW_UNKNOWN;
	string WindowClass = WINDOW_UNKNOWN;
	if (!window) {
		return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
	} else {
		if (window == RootWindow(dpy, XDefaultScreen(dpy)))
			return tuple<string, string, string>("(root window)", "(root window)", "(root window)");
		#ifdef NO_I18N
			char * win_name;
			if (!XFetchName(dpy, window, &win_name)) { /* Get window name if any */
				XFree(win_name);
				Window root_ret, parent_ret;
				unsigned int nChildren;
				Window * children = NULL;
				XQueryTree(dpy, window, &root_ret, &parent_ret, &children, &nChildren);
				if (children) 
					XFree(children);
				if ((XGetWMName(dpy, parent_ret, &tp)) && (recurse)) {
					XFree((void*)tp.value);
					return getWindowName(parent_ret, false);
				} else {
					if (tp.value)
						XFree((void*)tp.value);
					XFree(win_name);
					XClassHint * pClassHint = XAllocClassHint();
					if (XGetClassHint(dpy, window, pClassHint) > 0) {
						WindowNameFormal = pClassHint->res_name;
						WindowClass = pClassHint->res_class;  
						XFree(pClassHint->res_name);
						XFree(pClassHint->res_class);
					}
					XFree(pClassHint);
					return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
				}
			} else if (win_name) {
				const std::string retStr = win_name;
				XFree(win_name);
				XClassHint * pClassHint = XAllocClassHint();
				if (XGetClassHint(dpy, window, pClassHint) > 0) {
					WindowNameFormal = pClassHint->res_name;
					WindowClass = pClassHint->res_class;  
					XFree(pClassHint->res_name);
					XFree(pClassHint->res_class);
				}
				XFree(pClassHint);
				WindowName = retStr;
				return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
			}
		#else
			if (!XGetWMName(dpy, window, &tp)) { // Get window name if any
				if (tp.value)
					XFree((void*)tp.value);
				Window root_ret, parent_ret;
				unsigned int nChildren;
				Window * children = NULL;
				XQueryTree(dpy, window, &root_ret, &parent_ret, &children, &nChildren);
				if (children) 
					XFree(children);
				if ((XGetWMName(dpy, parent_ret, &tp)) && (recurse)) {
					if (tp.value)
						XFree((void*)tp.value);
					return getWindowName(dpy, parent_ret, false);
				} else {
					if (tp.value)
						XFree((void*)tp.value);
					XClassHint * pClassHint = XAllocClassHint();
					if (XGetClassHint(dpy, window, pClassHint) > 0) {
						WindowNameFormal = pClassHint->res_name;
						WindowClass = pClassHint->res_class;  
						XFree(pClassHint->res_name);
						XFree(pClassHint->res_class);
					}
					XFree(pClassHint);
					return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
				}
			} else if (tp.nitems > 0) {				
				XClassHint * pClassHint = XAllocClassHint();
				if (XGetClassHint(dpy, window, pClassHint) > 0) {
					WindowNameFormal = pClassHint->res_name;
					WindowClass = pClassHint->res_class;  
					XFree(pClassHint->res_name);
					XFree(pClassHint->res_class);
				}
				XFree(pClassHint);
				
				std::string retStr;
				int count = 0, i, ret;
				char **list = NULL;
				ret = XmbTextPropertyToTextList(dpy, &tp, &list, &count);
				if((ret == Success || ret > 0) && list != NULL) {
					for(i=0; i<count; i++)
						retStr += (const char *) list[i];
					XFree((void*)tp.value);
					XFreeStringList(list);
					WindowName = retStr;
					return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
				} else {
					XFree((void*)tp.value);
					if (list)
						XFreeStringList(list);
					retStr = (const char *) tp.value;
					WindowName = retStr;
					return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
				}
			}
		#endif
		else {
			return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
		}
	}	

	return tuple<string, string, string>(WindowName, WindowNameFormal, WindowClass);
}

/**
 * \brief  Initialize the focus watcher (create a new thread and start watching)
 */
void X11FocusWatcher::init() {
	if (mWatching)
		return;
	boost::thread thrd(mThreadProc);
}

/**
 * \brief  Test is an application is running by checking for its window title
 * \param  WindowTitle The title of the window to find
 *
 * Note this opens a new display so that the focus watcher
 * can remain using single threaded X11
 */
bool X11FocusWatcher::isApplicationRunning(std::string WindowTitle) {
	Display * Dsp;
	if ( (Dsp = XOpenDisplay(mDisplayName.c_str())) == NULL )
		return false;
	
	Window RootRet, ParentRet;
	unsigned int nChildren;
	Window * Children = NULL;
	XQueryTree(Dsp, RootWindow(Dsp, DefaultScreen(Dsp)), &RootRet, &ParentRet, &Children, &nChildren);
	for (unsigned int lp = 0; lp < nChildren; lp ++) {
		tuple<string, string, string> WindowInfo = getWindowName(Dsp, Children[lp]);
		if (stringconverter::toLower(WindowInfo.get<0>()).find(stringconverter::toLower(WindowTitle)) != string::npos) {
			XFree(Children);	
			XCloseDisplay(Dsp);
			return true;
		}
	}
	if (Children)
		XFree(Children);
	XCloseDisplay(Dsp);
	return false;
}

/**
 * \brief  Check if the event is a useless event
 * \return Check if the event is a null event
 */
bool X11FocusEvent::isNull() {
	if ( (WindowName == TITLE_UNKNOWN) && (WindowNameFormal == WINDOW_UNKNOWN) && (WindowClass == WINDOW_UNKNOWN) )
		return true;
	return false;
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
		cerr << "Unable to Open X11 Display [" << (mDisplayName == "" ? "Default" : mDisplayName) << "] -- Per application mappings will not work!" << endl;
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
 * \brief  != operator
 * \param  Event The test event
 */
bool X11FocusEvent::operator != (X11FocusEvent const & Event) {
	if ( (EventType == Event.EventType) &&
	     (WindowClass == Event.WindowClass) &&
	     (WindowName == Event.WindowName) &&
	     (WindowNameFormal == Event.WindowNameFormal) )
		return false;
	return true;
}

/**
 * \brief  == operator
 * \param  Event The test event
 */
bool X11FocusEvent::operator == (X11FocusEvent const & Event) {
	if ( (EventType == Event.EventType) &&
	     (WindowClass == Event.WindowClass) &&
	     (WindowName == Event.WindowName) &&
	     (WindowNameFormal == Event.WindowNameFormal) )
		return true;
	return false;
}

/**
 * \brief  Set all windows to report the FocusChangeMask
 */
void X11FocusWatcher::setFocusEventMasks() {
	Window RootRet, ParentRet;
	unsigned int nChildren;
	Window * Children = NULL;
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
	// open the display
	if ( (!openDisplay(mDisplayName)) || (mWatching) )
		return;
		
	// init
	mWatching = true;
	Window window;
	int revert_to_return;
	string WindowName;
		
	// Watch for focus changes	
	mWatching = true;
	while (mWatching) {
		// reset focus event masks
		setFocusEventMasks();
		
		// get the next event
		// manually check for focus changes since brand new windows 
		// might not have the proper event focus mask yet
		XEvent event;
		XGetInputFocus(mDisplay, &window, &revert_to_return);
		if (mCurrentWindow != window) {
			event.type = FocusIn;
			event.xany.window = window;
		} else {
			XNextEvent(mDisplay, &event);
		}
		
		// handle the event
		switch (event.type) {
		case FocusIn: {
			// avoid duplicate events
			if (mCurrentWindow == event.xany.window)
				break;
			X11FocusEvent Event = createFocusEvent(event.xany.window, X11FOCUSEVENT_IN);
			if ( (!Event.isNull()) && (Event != mLastEventIn) ) {
				mCurrentWindow = event.xany.window;
				onFocusIn(Event);
				mLastEventIn = Event;
			}
			break; }
		case FocusOut: {
			X11FocusEvent Event = createFocusEvent(event.xany.window, X11FOCUSEVENT_OUT);
			if ( (!Event.isNull()) && (Event != mLastEventOut) ) {
				onFocusOut(Event);
				mLastEventOut = Event;
			}
			break; }
		default:
			cdbg << "Unkown Event Type: " << event.type << endl;		
			break;
		}
	}

	// we're shuttind down! close the display
	closeDisplay();
}
