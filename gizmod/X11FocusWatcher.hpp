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
#include <boost/thread/thread.hpp>

//////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////

/**
 * \enum   X11FocusEventType
 * \brief  Type that indicates the type of X11FocusEvent
 */
typedef enum {
	X11FOCUSEVENT_IN,
	X11FOCUSEVENT_OUT
} X11FocusEventType;

//////////////////////////////////////////////////////////////////////////////
// X11FocusEvent Class Definition
///////////////////////////////////////

/**
 * \class  X11FocusEvent
 * \brief  Data structure that holds information about X11 Focus events
 *
 * Note that there is NO GUARANTEE that event orders are logical
 * For example, FOCUS_IN events might occur BEFORE a FOCUS_OUT
 * event, however, the events are true -- The current focus will
 * always be the last event with a FOCUS_IN type.
 *
 * This is due to the way X (and your WM's focus stealing prevention)
 * works (or perhaps doesn't work).
 *
 */
class X11FocusEvent {
public:	
	// public member variables
	X11FocusEventType		EventType;		///< The type of event
	std::string			WindowName;		///< Name of the Window as displayed in title bar
	std::string			WindowNameFormal;	///< Strict Name of the Window
	std::string			WindowClass;		///< Class of the Window
	
	// public functions

	// construction / deconstruction
	X11FocusEvent(X11FocusEventType eventType, std::string windowName, std::string windowNameFormal, std::string windowClass);
	X11FocusEvent(X11FocusEvent const & Event);
	virtual ~X11FocusEvent();

private:
	// private functions
		
	// private member variables
};

//////////////////////////////////////////////////////////////////////////////
// X11FocusWatcher Class Definition
///////////////////////////////////////

/**
 * \class  X11FocusWatcher
 * \brief  Watches for focus changes on X11 windows
 */
class X11FocusWatcher {
public:	
	// public functions
	void				init();			///< Initialize (create a thread and watch)
	virtual void			onFocusIn(X11FocusEvent const & Event); ///< Event triggered on a Focus In
	virtual void			onFocusOut(X11FocusEvent const & Event); ///< Event triggered on a Focus Out
	void 				shutdown();		///< Shutdown the thread that watches for focus changes

	// construction / deconstruction
	X11FocusWatcher();
	virtual ~X11FocusWatcher();
	
	// public static functions
	static int			x11ErrorHandler(Display * display, XErrorEvent * error); ///< Error handler
	static int			x11IOErrorHandler(Display * display); ///< IO error handler

private:
	// private functions
	void				closeDisplay();		///< Close the X11 display
	X11FocusEvent			createFocusEvent(Window const & window, X11FocusEventType EventType); ///< Create a X11FocusEvent from a Window
	std::string			getWindowName(Window const & window, bool recurse = true); ///< Get the string name of a window
	bool 				openDisplay(std::string DisplayName); ///< Open an X11 display
	void 				setFocusEventMasks();	///< Set all windows to report the FocusChange event mask
	void				threadProc();		///< thread procedure
		
	// private member variables
	Window				mCurrentWindow;		///< Current foreground window
	Display	*			mDisplay;		///< X11 Display
	std::string			mDisplayName;		///< Name of the display to open
	int				mScreen;		///< X11 Screen
	bool				mWatching;		///< Should we continue to watch the active window?
	
	/**
	 * Thread callback procedure struct
	 */
	struct X11FocusWatcherThreadProc {
		X11FocusWatcherThreadProc(X11FocusWatcher * pWatcher) : mpWatcher(pWatcher) {};
		
		/// Thread proc
		void operator()() {
			mpWatcher->threadProc();
		}
		
		X11FocusWatcher * 	mpWatcher;		///< The associated focus watcher
	};		
	X11FocusWatcherThreadProc	mThreadProc;		///< The thread procedure instance
};

#endif // __X11FocusWatcher_h
