    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoKeyDefPythonExposures.hpp
*** \brief GizmoKeyDefPythonExposures header
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

#ifndef __GizmoKeyDefPythonExposures_h
#define __GizmoKeyDefPythonExposures_h

#include "GizmoKeyDefs.hpp"

//////////////////////////////////////////////////////////////////////////////
// Typedef, enum's
///////////////////////////////////////

/**
 * \brief GizmoEventType Python enum export
 */
enum_<GizmoEventType>("GizmoEventType")
	.value("EV_SYN",        	GIZMO_EV_SYN)			///< GIZMO_EV_SYN
	.value("EV_KEY",        	GIZMO_EV_KEY)			///< GIZMO_EV_KEY
	.value("EV_REL",        	GIZMO_EV_REL)			///< GIZMO_EV_REL
	.value("EV_ABS",        	GIZMO_EV_ABS)			///< GIZMO_EV_ABS
	.value("EV_MSC",        	GIZMO_EV_MSC)			///< GIZMO_EV_MSC
	.value("EV_SW", 		GIZMO_EV_SW)			///< GIZMO_EV_SW
	.value("EV_LED",        	GIZMO_EV_LED)			///< GIZMO_EV_LED
	.value("EV_SND",        	GIZMO_EV_SND)			///< GIZMO_EV_SND
	.value("EV_REP",        	GIZMO_EV_REP)			///< GIZMO_EV_REP
	.value("EV_FF",	 		GIZMO_EV_FF)			///< GIZMO_EV_FF
	.value("EV_PWR",        	GIZMO_EV_PWR)			///< GIZMO_EV_PWR
	.value("EV_FF_STATUS",  	GIZMO_EV_FF_STATUS)		///< GIZMO_EV_FF_STATUS
	.value("EV_MAX",        	GIZMO_EV_MAX)			///< GIZMO_EV_MAX
	;
	
/**
 * \brief GizmoMouseAxis Python enum export
 */
enum_<GizmoMouseAxis>("GizmoMouseAxis")
	.value("X",        	GIZMO_MOUSE_AXIS_X)		///< GIZMO_MOUSE_AXIS_X
	.value("Y",        	GIZMO_MOUSE_AXIS_Y)		///< GIZMO_MOUSE_AXIS_Y
	.value("Z",     	GIZMO_MOUSE_AXIS_Z)		///< GIZMO_MOUSE_AXIS_Z
	.value("WHEEL",     	GIZMO_MOUSE_AXIS_Z)		///< GIZMO_MOUSE_AXIS_Z
	;
	
/**
 * \brief GizmoKey Python enum export
 */
enum_<GizmoKey>("GizmoKey")
	.value("KEY_RESERVED",  	GIZMO_KEY_RESERVED)		///< GIZMO_KEY_RESERVED
	.value("KEY_ESC",       	GIZMO_KEY_ESC)			///< GIZMO_KEY_ESC
	.value("KEY_1",			GIZMO_KEY_1)			///< GIZMO_KEY_1
	.value("KEY_2", 		GIZMO_KEY_2)			///< GIZMO_KEY_2
	.value("KEY_3", 		GIZMO_KEY_3)			///< GIZMO_KEY_3
	.value("KEY_4",			GIZMO_KEY_4)			///< GIZMO_KEY_4
	.value("KEY_5", 		GIZMO_KEY_5)			///< GIZMO_KEY_5
	.value("KEY_6", 		GIZMO_KEY_6)			///< GIZMO_KEY_6
	.value("KEY_7", 		GIZMO_KEY_7)			///< GIZMO_KEY_7
	.value("KEY_8", 		GIZMO_KEY_8)			///< GIZMO_KEY_8
	.value("KEY_9", 		GIZMO_KEY_9)			///< GIZMO_KEY_9
	.value("KEY_0", 		GIZMO_KEY_0)			///< GIZMO_KEY_0
	.value("KEY_MINUS",     	GIZMO_KEY_MINUS)		///< GIZMO_KEY_MINUS
	.value("KEY_EQUAL",     	GIZMO_KEY_EQUAL)		///< GIZMO_KEY_EQUAL
	.value("KEY_BACKSPACE", 	GIZMO_KEY_BACKSPACE)		///< GIZMO_KEY_BACKSPACE
	.value("KEY_TAB",       	GIZMO_KEY_TAB)			///< GIZMO_KEY_TAB
	.value("KEY_Q", 		GIZMO_KEY_Q)			///< GIZMO_KEY_Q
	.value("KEY_W", 		GIZMO_KEY_W)			///< GIZMO_KEY_W
	.value("KEY_E", 		GIZMO_KEY_E)			///< GIZMO_KEY_E
	.value("KEY_R", 		GIZMO_KEY_R)			///< GIZMO_KEY_R
	.value("KEY_T", 		GIZMO_KEY_T)			///< GIZMO_KEY_T
	.value("KEY_Y", 		GIZMO_KEY_Y)			///< GIZMO_KEY_Y
	.value("KEY_U", 		GIZMO_KEY_U)			///< GIZMO_KEY_U
	.value("KEY_I", 		GIZMO_KEY_I)			///< GIZMO_KEY_I
	.value("KEY_O", 		GIZMO_KEY_O)			///< GIZMO_KEY_O
	.value("KEY_P", 		GIZMO_KEY_P)			///< GIZMO_KEY_P
	.value("KEY_LEFTBRACE", 	GIZMO_KEY_LEFTBRACE)		///< GIZMO_KEY_LEFTBRACE
	.value("KEY_RIGHTBRACE",        GIZMO_KEY_RIGHTBRACE)		///< GIZMO_KEY_RIGHTBRACE
	.value("KEY_ENTER",     	GIZMO_KEY_ENTER)		///< GIZMO_KEY_ENTER
	.value("KEY_LEFTCTRL",  	GIZMO_KEY_LEFTCTRL)		///< GIZMO_KEY_LEFTCTRL
	.value("KEY_A", 		GIZMO_KEY_A)			///< GIZMO_KEY_A
	.value("KEY_S", 		GIZMO_KEY_S)			///< GIZMO_KEY_S
	.value("KEY_D", 		GIZMO_KEY_D)			///< GIZMO_KEY_D
	.value("KEY_F", 		GIZMO_KEY_F)			///< GIZMO_KEY_F
	.value("KEY_G", 		GIZMO_KEY_G)			///< GIZMO_KEY_G
	.value("KEY_H", 		GIZMO_KEY_H)			///< GIZMO_KEY_H
	.value("KEY_J", 		GIZMO_KEY_J)			///< GIZMO_KEY_J
	.value("KEY_K", 		GIZMO_KEY_K)			///< GIZMO_KEY_K
	.value("KEY_L", 		GIZMO_KEY_L)			///< GIZMO_KEY_L
	.value("KEY_SEMICOLON", 	GIZMO_KEY_SEMICOLON)		///< GIZMO_KEY_SEMICOLON
	.value("KEY_APOSTROPHE",        GIZMO_KEY_APOSTROPHE)		///< GIZMO_KEY_APOSTROPHE
	.value("KEY_GRAVE",     	GIZMO_KEY_GRAVE)		///< GIZMO_KEY_GRAVE
	.value("KEY_LEFTSHIFT", 	GIZMO_KEY_LEFTSHIFT)		///< GIZMO_KEY_LEFTSHIFT
	.value("KEY_BACKSLASH", 	GIZMO_KEY_BACKSLASH)		///< GIZMO_KEY_BACKSLASH
	.value("KEY_Z", 		GIZMO_KEY_Z)			///< GIZMO_KEY_Z
	.value("KEY_X", 		GIZMO_KEY_X)			///< GIZMO_KEY_X
	.value("KEY_C", 		GIZMO_KEY_C)			///< GIZMO_KEY_C
	.value("KEY_V", 		GIZMO_KEY_V)			///< GIZMO_KEY_V
	.value("KEY_B", 		GIZMO_KEY_B)			///< GIZMO_KEY_B
	.value("KEY_N", 		GIZMO_KEY_N)			///< GIZMO_KEY_N
	.value("KEY_M", 		GIZMO_KEY_M)			///< GIZMO_KEY_M
	.value("KEY_COMMA",     	GIZMO_KEY_COMMA)		///< GIZMO_KEY_COMMA
	.value("KEY_DOT",       	GIZMO_KEY_DOT)			///< GIZMO_KEY_DOT
	.value("KEY_SLASH",     	GIZMO_KEY_SLASH)		///< GIZMO_KEY_SLASH
	.value("KEY_RIGHTSHIFT",        GIZMO_KEY_RIGHTSHIFT)		///< GIZMO_KEY_RIGHTSHIFT
	.value("KEY_KPASTERISK",        GIZMO_KEY_KPASTERISK)		///< GIZMO_KEY_KPASTERISK
	.value("KEY_LEFTALT",   	GIZMO_KEY_LEFTALT)		///< GIZMO_KEY_LEFTALT
	.value("KEY_SPACE",     	GIZMO_KEY_SPACE)		///< GIZMO_KEY_SPACE
	.value("KEY_CAPSLOCK",  	GIZMO_KEY_CAPSLOCK)		///< GIZMO_KEY_CAPSLOCK
	.value("KEY_F1",        	GIZMO_KEY_F1)			///< GIZMO_KEY_F1
	.value("KEY_F2",        	GIZMO_KEY_F2)			///< GIZMO_KEY_F2
	.value("KEY_F3",        	GIZMO_KEY_F3)			///< GIZMO_KEY_F3
	.value("KEY_F4",        	GIZMO_KEY_F4)			///< GIZMO_KEY_F4
	.value("KEY_F5",        	GIZMO_KEY_F5)			///< GIZMO_KEY_F5
	.value("KEY_F6",        	GIZMO_KEY_F6)			///< GIZMO_KEY_F6
	.value("KEY_F7",        	GIZMO_KEY_F7)			///< GIZMO_KEY_F7
	.value("KEY_F8",        	GIZMO_KEY_F8)			///< GIZMO_KEY_F8
	.value("KEY_F9",        	GIZMO_KEY_F9)			///< GIZMO_KEY_F9
	.value("KEY_F10",       	GIZMO_KEY_F10)			///< GIZMO_KEY_F10
	.value("KEY_NUMLOCK",   	GIZMO_KEY_NUMLOCK)		///< GIZMO_KEY_NUMLOCK
	.value("KEY_SCROLLLOCK",        GIZMO_KEY_SCROLLLOCK)		///< GIZMO_KEY_SCROLLLOCK
	.value("KEY_KP7",       	GIZMO_KEY_KP7)			///< GIZMO_KEY_KP7
	.value("KEY_KP8",       	GIZMO_KEY_KP8)			///< GIZMO_KEY_KP8
	.value("KEY_KP9",       	GIZMO_KEY_KP9)			///< GIZMO_KEY_KP9
	.value("KEY_KPMINUS",   	GIZMO_KEY_KPMINUS)		///< GIZMO_KEY_KPMINUS
	.value("KEY_KP4",       	GIZMO_KEY_KP4)			///< GIZMO_KEY_KP4
	.value("KEY_KP5",       	GIZMO_KEY_KP5)			///< GIZMO_KEY_KP5
	.value("KEY_KP6",       	GIZMO_KEY_KP6)			///< GIZMO_KEY_KP6
	.value("KEY_KPPLUS",    	GIZMO_KEY_KPPLUS)		///< GIZMO_KEY_KPPLUS
	.value("KEY_KP1",       	GIZMO_KEY_KP1)			///< GIZMO_KEY_KP1
	.value("KEY_KP2",       	GIZMO_KEY_KP2)			///< GIZMO_KEY_KP2
	.value("KEY_KP3",       	GIZMO_KEY_KP3)			///< GIZMO_KEY_KP3
	.value("KEY_KP0",       	GIZMO_KEY_KP0)			///< GIZMO_KEY_KP0
	.value("KEY_KPDOT",     	GIZMO_KEY_KPDOT)		///< GIZMO_KEY_KPDOT
	.value("KEY_ZENKAKUHANKAKU",    GIZMO_KEY_ZENKAKUHANKAKU)	///< GIZMO_KEY_ZENKAKUHANKAKU
	.value("KEY_102ND",     	GIZMO_KEY_102ND)		///< GIZMO_KEY_102ND
	.value("KEY_F11",       	GIZMO_KEY_F11)			///< GIZMO_KEY_F11
	.value("KEY_F12",       	GIZMO_KEY_F12)			///< GIZMO_KEY_F12
	.value("KEY_RO",        	GIZMO_KEY_RO)			///< GIZMO_KEY_RO
	.value("KEY_KATAKANA",  	GIZMO_KEY_KATAKANA)		///< GIZMO_KEY_KATAKANA
	.value("KEY_HIRAGANA",  	GIZMO_KEY_HIRAGANA)		///< GIZMO_KEY_HIRAGANA
	.value("KEY_HENKAN",    	GIZMO_KEY_HENKAN)		///< GIZMO_KEY_HENKAN
	.value("KEY_KATAKANAHIRAGANA",  GIZMO_KEY_KATAKANAHIRAGANA)	///< GIZMO_KEY_KATAKANAHIRAGANA
	.value("KEY_MUHENKAN",  	GIZMO_KEY_MUHENKAN)		///< GIZMO_KEY_MUHENKAN
	.value("KEY_KPJPCOMMA", 	GIZMO_KEY_KPJPCOMMA)		///< GIZMO_KEY_KPJPCOMMA
	.value("KEY_KPENTER",   	GIZMO_KEY_KPENTER)		///< GIZMO_KEY_KPENTER
	.value("KEY_RIGHTCTRL", 	GIZMO_KEY_RIGHTCTRL)		///< GIZMO_KEY_RIGHTCTRL
	.value("KEY_KPSLASH",   	GIZMO_KEY_KPSLASH)		///< GIZMO_KEY_KPSLASH
	.value("KEY_SYSRQ",     	GIZMO_KEY_SYSRQ)		///< GIZMO_KEY_SYSRQ
	.value("KEY_RIGHTALT",  	GIZMO_KEY_RIGHTALT)		///< GIZMO_KEY_RIGHTALT
	.value("KEY_LINEFEED",  	GIZMO_KEY_LINEFEED)		///< GIZMO_KEY_LINEFEED
	.value("KEY_HOME",      	GIZMO_KEY_HOME)			///< GIZMO_KEY_HOME
	.value("KEY_UP",        	GIZMO_KEY_UP)			///< GIZMO_KEY_UP
	.value("KEY_PAGEUP",    	GIZMO_KEY_PAGEUP)		///< GIZMO_KEY_PAGEUP
	.value("KEY_LEFT",      	GIZMO_KEY_LEFT)			///< GIZMO_KEY_LEFT
	.value("KEY_RIGHT",     	GIZMO_KEY_RIGHT)		///< GIZMO_KEY_RIGHT
	.value("KEY_END",       	GIZMO_KEY_END)			///< GIZMO_KEY_END
	.value("KEY_DOWN",      	GIZMO_KEY_DOWN)			///< GIZMO_KEY_DOWN
	.value("KEY_PAGEDOWN",  	GIZMO_KEY_PAGEDOWN)		///< GIZMO_KEY_PAGEDOWN
	.value("KEY_INSERT",    	GIZMO_KEY_INSERT)		///< GIZMO_KEY_INSERT
	.value("KEY_DELETE",    	GIZMO_KEY_DELETE)		///< GIZMO_KEY_DELETE
	.value("KEY_MACRO",     	GIZMO_KEY_MACRO)		///< GIZMO_KEY_MACRO
	.value("KEY_MUTE",      	GIZMO_KEY_MUTE)			///< GIZMO_KEY_MUTE
	.value("KEY_VOLUMEDOWN",        GIZMO_KEY_VOLUMEDOWN)		///< GIZMO_KEY_VOLUMEDOWN
	.value("KEY_VOLUMEUP",  	GIZMO_KEY_VOLUMEUP)		///< GIZMO_KEY_VOLUMEUP
	.value("KEY_POWER",     	GIZMO_KEY_POWER)		///< GIZMO_KEY_POWER
	.value("KEY_KPEQUAL",   	GIZMO_KEY_KPEQUAL)		///< GIZMO_KEY_KPEQUAL
	.value("KEY_KPPLUSMINUS",       GIZMO_KEY_KPPLUSMINUS)		///< GIZMO_KEY_KPPLUSMINUS
	.value("KEY_PAUSE",     	GIZMO_KEY_PAUSE)		///< GIZMO_KEY_PAUSE
	.value("KEY_KPCOMMA",   	GIZMO_KEY_KPCOMMA)		///< GIZMO_KEY_KPCOMMA
	.value("KEY_HANGEUL",   	GIZMO_KEY_HANGEUL)		///< GIZMO_KEY_HANGEUL
	.value("KEY_HANJA",     	GIZMO_KEY_HANJA)		///< GIZMO_KEY_HANJA
	.value("KEY_YEN",       	GIZMO_KEY_YEN)			///< GIZMO_KEY_YEN
	.value("KEY_LEFTMETA",  	GIZMO_KEY_LEFTMETA)		///< GIZMO_KEY_LEFTMETA
	.value("KEY_RIGHTMETA", 	GIZMO_KEY_RIGHTMETA)		///< GIZMO_KEY_RIGHTMETA
	.value("KEY_COMPOSE",   	GIZMO_KEY_COMPOSE)		///< GIZMO_KEY_COMPOSE
	.value("KEY_STOP",      	GIZMO_KEY_STOP)			///< GIZMO_KEY_STOP
	.value("KEY_AGAIN",     	GIZMO_KEY_AGAIN)		///< GIZMO_KEY_AGAIN
	.value("KEY_PROPS",     	GIZMO_KEY_PROPS)		///< GIZMO_KEY_PROPS
	.value("KEY_UNDO",      	GIZMO_KEY_UNDO)			///< GIZMO_KEY_UNDO
	.value("KEY_FRONT",     	GIZMO_KEY_FRONT)		///< GIZMO_KEY_FRONT
	.value("KEY_COPY",      	GIZMO_KEY_COPY)			///< GIZMO_KEY_COPY
	.value("KEY_OPEN",      	GIZMO_KEY_OPEN)			///< GIZMO_KEY_OPEN
	.value("KEY_PASTE",     	GIZMO_KEY_PASTE)		///< GIZMO_KEY_PASTE
	.value("KEY_FIND",      	GIZMO_KEY_FIND)			///< GIZMO_KEY_FIND
	.value("KEY_CUT",       	GIZMO_KEY_CUT)			///< GIZMO_KEY_CUT
	.value("KEY_HELP",      	GIZMO_KEY_HELP)			///< GIZMO_KEY_HELP
	.value("KEY_MENU",      	GIZMO_KEY_MENU)			///< GIZMO_KEY_MENU
	.value("KEY_CALC",      	GIZMO_KEY_CALC)			///< GIZMO_KEY_CALC
	.value("KEY_SETUP",     	GIZMO_KEY_SETUP)		///< GIZMO_KEY_SETUP
	.value("KEY_SLEEP",     	GIZMO_KEY_SLEEP)		///< GIZMO_KEY_SLEEP
	.value("KEY_WAKEUP",    	GIZMO_KEY_WAKEUP)		///< GIZMO_KEY_WAKEUP
	.value("KEY_FILE",      	GIZMO_KEY_FILE)			///< GIZMO_KEY_FILE
	.value("KEY_SENDFILE",  	GIZMO_KEY_SENDFILE)		///< GIZMO_KEY_SENDFILE
	.value("KEY_DELETEFILE",        GIZMO_KEY_DELETEFILE)		///< GIZMO_KEY_DELETEFILE
	.value("KEY_XFER",      	GIZMO_KEY_XFER)			///< GIZMO_KEY_XFER
	.value("KEY_PROG1",     	GIZMO_KEY_PROG1)		///< GIZMO_KEY_PROG1
	.value("KEY_PROG2",     	GIZMO_KEY_PROG2)		///< GIZMO_KEY_PROG2
	.value("KEY_WWW",       	GIZMO_KEY_WWW)			///< GIZMO_KEY_WWW
	.value("KEY_MSDOS",     	GIZMO_KEY_MSDOS)		///< GIZMO_KEY_MSDOS
	.value("KEY_COFFEE",    	GIZMO_KEY_COFFEE)		///< GIZMO_KEY_COFFEE
	.value("KEY_DIRECTION", 	GIZMO_KEY_DIRECTION)		///< GIZMO_KEY_DIRECTION
	.value("KEY_CYCLEWINDOWS",      GIZMO_KEY_CYCLEWINDOWS)		///< GIZMO_KEY_CYCLEWINDOWS
	.value("KEY_MAIL",      	GIZMO_KEY_MAIL)			///< GIZMO_KEY_MAIL
	.value("KEY_BOOKMARKS", 	GIZMO_KEY_BOOKMARKS)		///< GIZMO_KEY_BOOKMARKS
	.value("KEY_COMPUTER",  	GIZMO_KEY_COMPUTER)		///< GIZMO_KEY_COMPUTER
	.value("KEY_BACK",      	GIZMO_KEY_BACK)			///< GIZMO_KEY_BACK
	.value("KEY_FORWARD",   	GIZMO_KEY_FORWARD)		///< GIZMO_KEY_FORWARD
	.value("KEY_CLOSECD",   	GIZMO_KEY_CLOSECD)		///< GIZMO_KEY_CLOSECD
	.value("KEY_EJECTCD",   	GIZMO_KEY_EJECTCD)		///< GIZMO_KEY_EJECTCD
	.value("KEY_EJECTCLOSECD",      GIZMO_KEY_EJECTCLOSECD)		///< GIZMO_KEY_EJECTCLOSECD
	.value("KEY_NEXTSONG",  	GIZMO_KEY_NEXTSONG)		///< GIZMO_KEY_NEXTSONG
	.value("KEY_PLAYPAUSE", 	GIZMO_KEY_PLAYPAUSE)		///< GIZMO_KEY_PLAYPAUSE
	.value("KEY_PREVIOUSSONG",      GIZMO_KEY_PREVIOUSSONG)		///< GIZMO_KEY_PREVIOUSSONG
	.value("KEY_STOPCD",    	GIZMO_KEY_STOPCD)		///< GIZMO_KEY_STOPCD
	.value("KEY_RECORD",    	GIZMO_KEY_RECORD)		///< GIZMO_KEY_RECORD
	.value("KEY_REWIND",    	GIZMO_KEY_REWIND)		///< GIZMO_KEY_REWIND
	.value("KEY_PHONE",     	GIZMO_KEY_PHONE)		///< GIZMO_KEY_PHONE
	.value("KEY_ISO",       	GIZMO_KEY_ISO)			///< GIZMO_KEY_ISO
	.value("KEY_CONFIG",    	GIZMO_KEY_CONFIG)		///< GIZMO_KEY_CONFIG
	.value("KEY_HOMEPAGE",  	GIZMO_KEY_HOMEPAGE)		///< GIZMO_KEY_HOMEPAGE
	.value("KEY_REFRESH",   	GIZMO_KEY_REFRESH)		///< GIZMO_KEY_REFRESH
	.value("KEY_EXIT",      	GIZMO_KEY_EXIT)			///< GIZMO_KEY_EXIT
	.value("KEY_MOVE",      	GIZMO_KEY_MOVE)			///< GIZMO_KEY_MOVE
	.value("KEY_EDIT",      	GIZMO_KEY_EDIT)			///< GIZMO_KEY_EDIT
	.value("KEY_SCROLLUP",  	GIZMO_KEY_SCROLLUP)		///< GIZMO_KEY_SCROLLUP
	.value("KEY_SCROLLDOWN",        GIZMO_KEY_SCROLLDOWN)		///< GIZMO_KEY_SCROLLDOWN
	.value("KEY_KPLEFTPAREN",       GIZMO_KEY_KPLEFTPAREN)		///< GIZMO_KEY_KPLEFTPAREN
	.value("KEY_KPRIGHTPAREN",      GIZMO_KEY_KPRIGHTPAREN)		///< GIZMO_KEY_KPRIGHTPAREN
	.value("KEY_NEW",       	GIZMO_KEY_NEW)			///< GIZMO_KEY_NEW
	.value("KEY_REDO",      	GIZMO_KEY_REDO)			///< GIZMO_KEY_REDO
	.value("KEY_F13",       	GIZMO_KEY_F13)			///< GIZMO_KEY_F13
	.value("KEY_F14",       	GIZMO_KEY_F14)			///< GIZMO_KEY_F14
	.value("KEY_F15",       	GIZMO_KEY_F15)			///< GIZMO_KEY_F15
	.value("KEY_F16",       	GIZMO_KEY_F16)			///< GIZMO_KEY_F16
	.value("KEY_F17",       	GIZMO_KEY_F17)			///< GIZMO_KEY_F17
	.value("KEY_F18",       	GIZMO_KEY_F18)			///< GIZMO_KEY_F18
	.value("KEY_F19",       	GIZMO_KEY_F19)			///< GIZMO_KEY_F19
	.value("KEY_F20",       	GIZMO_KEY_F20)			///< GIZMO_KEY_F20
	.value("KEY_F21",       	GIZMO_KEY_F21)			///< GIZMO_KEY_F21
	.value("KEY_F22",       	GIZMO_KEY_F22)			///< GIZMO_KEY_F22
	.value("KEY_F23",       	GIZMO_KEY_F23)			///< GIZMO_KEY_F23
	.value("KEY_F24",       	GIZMO_KEY_F24)			///< GIZMO_KEY_F24
	.value("KEY_PLAYCD",    	GIZMO_KEY_PLAYCD)		///< GIZMO_KEY_PLAYCD
	.value("KEY_PAUSECD",   	GIZMO_KEY_PAUSECD)		///< GIZMO_KEY_PAUSECD
	.value("KEY_PROG3",     	GIZMO_KEY_PROG3)		///< GIZMO_KEY_PROG3
	.value("KEY_PROG4",     	GIZMO_KEY_PROG4)		///< GIZMO_KEY_PROG4
	.value("KEY_SUSPEND",   	GIZMO_KEY_SUSPEND)		///< GIZMO_KEY_SUSPEND
	.value("KEY_CLOSE",     	GIZMO_KEY_CLOSE)		///< GIZMO_KEY_CLOSE
	.value("KEY_PLAY",      	GIZMO_KEY_PLAY)			///< GIZMO_KEY_PLAY
	.value("KEY_FASTFORWARD",       GIZMO_KEY_FASTFORWARD)		///< GIZMO_KEY_FASTFORWARD
	.value("KEY_BASSBOOST", 	GIZMO_KEY_BASSBOOST)		///< GIZMO_KEY_BASSBOOST
	.value("KEY_PRINT",     	GIZMO_KEY_PRINT)		///< GIZMO_KEY_PRINT
	.value("KEY_HP",        	GIZMO_KEY_HP)			///< GIZMO_KEY_HP
	.value("KEY_CAMERA",    	GIZMO_KEY_CAMERA)		///< GIZMO_KEY_CAMERA
	.value("KEY_SOUND",     	GIZMO_KEY_SOUND)		///< GIZMO_KEY_SOUND
	.value("KEY_QUESTION",  	GIZMO_KEY_QUESTION)		///< GIZMO_KEY_QUESTION
	.value("KEY_EMAIL",     	GIZMO_KEY_EMAIL)		///< GIZMO_KEY_EMAIL
	.value("KEY_CHAT",      	GIZMO_KEY_CHAT)			///< GIZMO_KEY_CHAT
	.value("KEY_SEARCH",    	GIZMO_KEY_SEARCH)		///< GIZMO_KEY_SEARCH
	.value("KEY_CONNECT",   	GIZMO_KEY_CONNECT)		///< GIZMO_KEY_CONNECT
	.value("KEY_FINANCE",   	GIZMO_KEY_FINANCE)		///< GIZMO_KEY_FINANCE
	.value("KEY_SPORT",     	GIZMO_KEY_SPORT)		///< GIZMO_KEY_SPORT
	.value("KEY_SHOP",      	GIZMO_KEY_SHOP)			///< GIZMO_KEY_SHOP
	.value("KEY_ALTERASE",  	GIZMO_KEY_ALTERASE)		///< GIZMO_KEY_ALTERASE
	.value("KEY_CANCEL",    	GIZMO_KEY_CANCEL)		///< GIZMO_KEY_CANCEL
	.value("KEY_BRIGHTNESSDOWN",    GIZMO_KEY_BRIGHTNESSDOWN)	///< GIZMO_KEY_BRIGHTNESSDOWN
	.value("KEY_BRIGHTNESSUP",      GIZMO_KEY_BRIGHTNESSUP)		///< GIZMO_KEY_BRIGHTNESSUP
	.value("KEY_MEDIA",     	GIZMO_KEY_MEDIA)		///< GIZMO_KEY_MEDIA
	.value("KEY_SWITCHVIDEOMODE",   GIZMO_KEY_SWITCHVIDEOMODE)	///< GIZMO_KEY_SWITCHVIDEOMODE
	.value("KEY_KBDILLUMTOGGLE",    GIZMO_KEY_KBDILLUMTOGGLE)	///< GIZMO_KEY_KBDILLUMTOGGLE
	.value("KEY_KBDILLUMDOWN",      GIZMO_KEY_KBDILLUMDOWN)		///< GIZMO_KEY_KBDILLUMDOWN
	.value("KEY_KBDILLUMUP",        GIZMO_KEY_KBDILLUMUP)		///< GIZMO_KEY_KBDILLUMUP
	.value("KEY_SEND",      	GIZMO_KEY_SEND)			///< GIZMO_KEY_SEND
	.value("KEY_REPLY",     	GIZMO_KEY_REPLY)		///< GIZMO_KEY_REPLY
	.value("KEY_FORWARDMAIL",       GIZMO_KEY_FORWARDMAIL)		///< GIZMO_KEY_FORWARDMAIL
	.value("KEY_SAVE",      	GIZMO_KEY_SAVE)			///< GIZMO_KEY_SAVE
	.value("KEY_DOCUMENTS", 	GIZMO_KEY_DOCUMENTS)		///< GIZMO_KEY_DOCUMENTS
	.value("KEY_BATTERY",   	GIZMO_KEY_BATTERY)		///< GIZMO_KEY_BATTERY
	.value("KEY_BLUETOOTH", 	GIZMO_KEY_BLUETOOTH)		///< GIZMO_KEY_BLUETOOTH
	.value("KEY_WLAN",      	GIZMO_KEY_WLAN)			///< GIZMO_KEY_WLAN
	.value("KEY_UNKNOWN",   	GIZMO_KEY_UNKNOWN)		///< GIZMO_KEY_UNKNOWN
	.value("BTN_MISC",      	GIZMO_BTN_MISC)			///< GIZMO_BTN_MISC
	.value("BTN_0", 		GIZMO_BTN_0)			///< GIZMO_BTN_0
	.value("BTN_1", 		GIZMO_BTN_1)			///< GIZMO_BTN_1
	.value("BTN_2", 		GIZMO_BTN_2)			///< GIZMO_BTN_2
	.value("BTN_3", 		GIZMO_BTN_3)			///< GIZMO_BTN_3
	.value("BTN_4", 		GIZMO_BTN_4)			///< GIZMO_BTN_4
	.value("BTN_5", 		GIZMO_BTN_5)			///< GIZMO_BTN_5
	.value("BTN_6", 		GIZMO_BTN_6)			///< GIZMO_BTN_6
	.value("BTN_7", 		GIZMO_BTN_7)			///< GIZMO_BTN_7
	.value("BTN_8", 		GIZMO_BTN_8)			///< GIZMO_BTN_8
	.value("BTN_9", 		GIZMO_BTN_9)			///< GIZMO_BTN_9
	.value("BTN_MOUSE",     	GIZMO_BTN_MOUSE)		///< GIZMO_BTN_MOUSE
	.value("BTN_LEFT",      	GIZMO_BTN_LEFT)			///< GIZMO_BTN_LEFT
	.value("BTN_RIGHT",     	GIZMO_BTN_RIGHT)		///< GIZMO_BTN_RIGHT
	.value("BTN_MIDDLE",    	GIZMO_BTN_MIDDLE)		///< GIZMO_BTN_MIDDLE
	.value("BTN_SIDE",      	GIZMO_BTN_SIDE)			///< GIZMO_BTN_SIDE
	.value("BTN_EXTRA",     	GIZMO_BTN_EXTRA)		///< GIZMO_BTN_EXTRA
	.value("BTN_FORWARD",   	GIZMO_BTN_FORWARD)		///< GIZMO_BTN_FORWARD
	.value("BTN_BACK",      	GIZMO_BTN_BACK)			///< GIZMO_BTN_BACK
	.value("BTN_TASK",      	GIZMO_BTN_TASK)			///< GIZMO_BTN_TASK
	.value("BTN_JOYSTICK",  	GIZMO_BTN_JOYSTICK)		///< GIZMO_BTN_JOYSTICK
	.value("BTN_TRIGGER",   	GIZMO_BTN_TRIGGER)		///< GIZMO_BTN_TRIGGER
	.value("BTN_THUMB",     	GIZMO_BTN_THUMB)		///< GIZMO_BTN_THUMB
	.value("BTN_THUMB2",    	GIZMO_BTN_THUMB2)		///< GIZMO_BTN_THUMB2
	.value("BTN_TOP",       	GIZMO_BTN_TOP)			///< GIZMO_BTN_TOP
	.value("BTN_TOP2",      	GIZMO_BTN_TOP2)			///< GIZMO_BTN_TOP2
	.value("BTN_PINKIE",    	GIZMO_BTN_PINKIE)		///< GIZMO_BTN_PINKIE
	.value("BTN_BASE",      	GIZMO_BTN_BASE)			///< GIZMO_BTN_BASE
	.value("BTN_BASE2",     	GIZMO_BTN_BASE2)		///< GIZMO_BTN_BASE2
	.value("BTN_BASE3",     	GIZMO_BTN_BASE3)		///< GIZMO_BTN_BASE3
	.value("BTN_BASE4",     	GIZMO_BTN_BASE4)		///< GIZMO_BTN_BASE4
	.value("BTN_BASE5",     	GIZMO_BTN_BASE5)		///< GIZMO_BTN_BASE5
	.value("BTN_BASE6",     	GIZMO_BTN_BASE6)		///< GIZMO_BTN_BASE6
	.value("BTN_DEAD",      	GIZMO_BTN_DEAD)			///< GIZMO_BTN_DEAD
	.value("BTN_GAMEPAD",   	GIZMO_BTN_GAMEPAD)		///< GIZMO_BTN_GAMEPAD
	.value("BTN_A", 		GIZMO_BTN_A)			///< GIZMO_BTN_A
	.value("BTN_B", 		GIZMO_BTN_B)			///< GIZMO_BTN_B
	.value("BTN_C", 		GIZMO_BTN_C)			///< GIZMO_BTN_C
	.value("BTN_X", 		GIZMO_BTN_X)			///< GIZMO_BTN_X
	.value("BTN_Y", 		GIZMO_BTN_Y)			///< GIZMO_BTN_Y
	.value("BTN_Z", 		GIZMO_BTN_Z)			///< GIZMO_BTN_Z
	.value("BTN_TL",        	GIZMO_BTN_TL)			///< GIZMO_BTN_TL
	.value("BTN_TR",        	GIZMO_BTN_TR)			///< GIZMO_BTN_TR
	.value("BTN_TL2",       	GIZMO_BTN_TL2)			///< GIZMO_BTN_TL2
	.value("BTN_TR2",       	GIZMO_BTN_TR2)			///< GIZMO_BTN_TR2
	.value("BTN_SELECT",    	GIZMO_BTN_SELECT)		///< GIZMO_BTN_SELECT
	.value("BTN_START",     	GIZMO_BTN_START)		///< GIZMO_BTN_START
	.value("BTN_MODE",      	GIZMO_BTN_MODE)			///< GIZMO_BTN_MODE
	.value("BTN_THUMBL",    	GIZMO_BTN_THUMBL)		///< GIZMO_BTN_THUMBL
	.value("BTN_THUMBR",    	GIZMO_BTN_THUMBR)		///< GIZMO_BTN_THUMBR
	.value("BTN_DIGI",      	GIZMO_BTN_DIGI)			///< GIZMO_BTN_DIGI
	.value("BTN_TOOL_PEN",  	GIZMO_BTN_TOOL_PEN)		///< GIZMO_BTN_TOOL_PEN
	.value("BTN_TOOL_RUBBER",      	GIZMO_BTN_TOOL_RUBBER)		///< GIZMO_BTN_TOOL_RUBBER
	.value("BTN_TOOL_BRUSH",       	GIZMO_BTN_TOOL_BRUSH)		///< GIZMO_BTN_TOOL_BRUSH
	.value("BTN_TOOL_PENCIL",      	GIZMO_BTN_TOOL_PENCIL)		///< GIZMO_BTN_TOOL_PENCIL
	.value("BTN_TOOL_AIRBRUSH",    	GIZMO_BTN_TOOL_AIRBRUSH)	///< GIZMO_BTN_TOOL_AIRBRUSH
	.value("BTN_TOOL_FINGER",      	GIZMO_BTN_TOOL_FINGER)		///< GIZMO_BTN_TOOL_FINGER
	.value("BTN_TOOL_MOUSE",       	GIZMO_BTN_TOOL_MOUSE)		///< GIZMO_BTN_TOOL_MOUSE
	.value("BTN_TOOL_LENS", 	GIZMO_BTN_TOOL_LENS)		///< GIZMO_BTN_TOOL_LENS
	.value("BTN_TOUCH",     	GIZMO_BTN_TOUCH)		///< GIZMO_BTN_TOUCH
	.value("BTN_STYLUS",    	GIZMO_BTN_STYLUS)		///< GIZMO_BTN_STYLUS
	.value("BTN_STYLUS2",   	GIZMO_BTN_STYLUS2)		///< GIZMO_BTN_STYLUS2
	.value("BTN_TOOL_DOUBLETAP",   	GIZMO_BTN_TOOL_DOUBLETAP)	///< GIZMO_BTN_TOOL_DOUBLETAP
	.value("BTN_TOOL_TRIPLETAP",   	GIZMO_BTN_TOOL_TRIPLETAP)	///< GIZMO_BTN_TOOL_TRIPLETAP
	.value("BTN_WHEEL",     	GIZMO_BTN_WHEEL)		///< GIZMO_BTN_WHEEL
	.value("BTN_GEAR_DOWN", 	GIZMO_BTN_GEAR_DOWN)		///< GIZMO_BTN_GEAR_DOWN
	.value("BTN_GEAR_UP",   	GIZMO_BTN_GEAR_UP)		///< GIZMO_BTN_GEAR_UP
	.value("KEY_OK",        	GIZMO_KEY_OK)			///< GIZMO_KEY_OK
	.value("KEY_SELECT",    	GIZMO_KEY_SELECT)		///< GIZMO_KEY_SELECT
	.value("KEY_GOTO",      	GIZMO_KEY_GOTO)			///< GIZMO_KEY_GOTO
	.value("KEY_CLEAR",     	GIZMO_KEY_CLEAR)		///< GIZMO_KEY_CLEAR
	.value("KEY_POWER2",    	GIZMO_KEY_POWER2)		///< GIZMO_KEY_POWER2
	.value("KEY_OPTION",    	GIZMO_KEY_OPTION)		///< GIZMO_KEY_OPTION
	.value("KEY_INFO",      	GIZMO_KEY_INFO)			///< GIZMO_KEY_INFO
	.value("KEY_TIME",      	GIZMO_KEY_TIME)			///< GIZMO_KEY_TIME
	.value("KEY_VENDOR",    	GIZMO_KEY_VENDOR)		///< GIZMO_KEY_VENDOR
	.value("KEY_ARCHIVE",   	GIZMO_KEY_ARCHIVE)		///< GIZMO_KEY_ARCHIVE
	.value("KEY_PROGRAM",   	GIZMO_KEY_PROGRAM)		///< GIZMO_KEY_PROGRAM
	.value("KEY_CHANNEL",   	GIZMO_KEY_CHANNEL)		///< GIZMO_KEY_CHANNEL
	.value("KEY_FAVORITES", 	GIZMO_KEY_FAVORITES)		///< GIZMO_KEY_FAVORITES
	.value("KEY_EPG",       	GIZMO_KEY_EPG)			///< GIZMO_KEY_EPG
	.value("KEY_PVR",       	GIZMO_KEY_PVR)			///< GIZMO_KEY_PVR
	.value("KEY_MHP",       	GIZMO_KEY_MHP)			///< GIZMO_KEY_MHP
	.value("KEY_LANGUAGE",  	GIZMO_KEY_LANGUAGE)		///< GIZMO_KEY_LANGUAGE
	.value("KEY_TITLE",     	GIZMO_KEY_TITLE)		///< GIZMO_KEY_TITLE
	.value("KEY_SUBTITLE",  	GIZMO_KEY_SUBTITLE)		///< GIZMO_KEY_SUBTITLE
	.value("KEY_ANGLE",     	GIZMO_KEY_ANGLE)		///< GIZMO_KEY_ANGLE
	.value("KEY_ZOOM",      	GIZMO_KEY_ZOOM)			///< GIZMO_KEY_ZOOM
	.value("KEY_MODE",      	GIZMO_KEY_MODE)			///< GIZMO_KEY_MODE
	.value("KEY_KEYBOARD",  	GIZMO_KEY_KEYBOARD)		///< GIZMO_KEY_KEYBOARD
	.value("KEY_SCREEN",    	GIZMO_KEY_SCREEN)		///< GIZMO_KEY_SCREEN
	.value("KEY_PC",        	GIZMO_KEY_PC)			///< GIZMO_KEY_PC
	.value("KEY_TV",        	GIZMO_KEY_TV)			///< GIZMO_KEY_TV
	.value("KEY_TV2",       	GIZMO_KEY_TV2)			///< GIZMO_KEY_TV2
	.value("KEY_VCR",       	GIZMO_KEY_VCR)			///< GIZMO_KEY_VCR
	.value("KEY_VCR2",      	GIZMO_KEY_VCR2)			///< GIZMO_KEY_VCR2
	.value("KEY_SAT",       	GIZMO_KEY_SAT)			///< GIZMO_KEY_SAT
	.value("KEY_SAT2",      	GIZMO_KEY_SAT2)			///< GIZMO_KEY_SAT2
	.value("KEY_CD",        	GIZMO_KEY_CD)			///< GIZMO_KEY_CD
	.value("KEY_TAPE",      	GIZMO_KEY_TAPE)			///< GIZMO_KEY_TAPE
	.value("KEY_RADIO",     	GIZMO_KEY_RADIO)		///< GIZMO_KEY_RADIO
	.value("KEY_TUNER",     	GIZMO_KEY_TUNER)		///< GIZMO_KEY_TUNER
	.value("KEY_PLAYER",    	GIZMO_KEY_PLAYER)		///< GIZMO_KEY_PLAYER
	.value("KEY_TEXT",      	GIZMO_KEY_TEXT)			///< GIZMO_KEY_TEXT
	.value("KEY_DVD",       	GIZMO_KEY_DVD)			///< GIZMO_KEY_DVD
	.value("KEY_AUX",       	GIZMO_KEY_AUX)			///< GIZMO_KEY_AUX
	.value("KEY_MP3",       	GIZMO_KEY_MP3)			///< GIZMO_KEY_MP3
	.value("KEY_AUDIO",     	GIZMO_KEY_AUDIO)		///< GIZMO_KEY_AUDIO
	.value("KEY_VIDEO",     	GIZMO_KEY_VIDEO)		///< GIZMO_KEY_VIDEO
	.value("KEY_DIRECTORY", 	GIZMO_KEY_DIRECTORY)		///< GIZMO_KEY_DIRECTORY
	.value("KEY_LIST",      	GIZMO_KEY_LIST)			///< GIZMO_KEY_LIST
	.value("KEY_MEMO",      	GIZMO_KEY_MEMO)			///< GIZMO_KEY_MEMO
	.value("KEY_CALENDAR",  	GIZMO_KEY_CALENDAR)		///< GIZMO_KEY_CALENDAR
	.value("KEY_RED",       	GIZMO_KEY_RED)			///< GIZMO_KEY_RED
	.value("KEY_GREEN",     	GIZMO_KEY_GREEN)		///< GIZMO_KEY_GREEN
	.value("KEY_YELLOW",    	GIZMO_KEY_YELLOW)		///< GIZMO_KEY_YELLOW
	.value("KEY_BLUE",      	GIZMO_KEY_BLUE)			///< GIZMO_KEY_BLUE
	.value("KEY_CHANNELUP", 	GIZMO_KEY_CHANNELUP)		///< GIZMO_KEY_CHANNELUP
	.value("KEY_CHANNELDOWN",      	GIZMO_KEY_CHANNELDOWN)		///< GIZMO_KEY_CHANNELDOWN
	.value("KEY_FIRST",     	GIZMO_KEY_FIRST)		///< GIZMO_KEY_FIRST
	.value("KEY_LAST",      	GIZMO_KEY_LAST)			///< GIZMO_KEY_LAST
	.value("KEY_AB",        	GIZMO_KEY_AB)			///< GIZMO_KEY_AB
	.value("KEY_NEXT",      	GIZMO_KEY_NEXT)			///< GIZMO_KEY_NEXT
	.value("KEY_RESTART",   	GIZMO_KEY_RESTART)		///< GIZMO_KEY_RESTART
	.value("KEY_SLOW",      	GIZMO_KEY_SLOW)			///< GIZMO_KEY_SLOW
	.value("KEY_SHUFFLE",   	GIZMO_KEY_SHUFFLE)		///< GIZMO_KEY_SHUFFLE
	.value("KEY_BREAK",     	GIZMO_KEY_BREAK)		///< GIZMO_KEY_BREAK
	.value("KEY_PREVIOUS",  	GIZMO_KEY_PREVIOUS)		///< GIZMO_KEY_PREVIOUS
	.value("KEY_DIGITS",    	GIZMO_KEY_DIGITS)		///< GIZMO_KEY_DIGITS
	.value("KEY_TEEN",      	GIZMO_KEY_TEEN)			///< GIZMO_KEY_TEEN
	.value("KEY_TWEN",      	GIZMO_KEY_TWEN)			///< GIZMO_KEY_TWEN
	.value("KEY_DEL_EOL",   	GIZMO_KEY_DEL_EOL)		///< GIZMO_KEY_DEL_EOL
	.value("KEY_DEL_EOS",   	GIZMO_KEY_DEL_EOS)		///< GIZMO_KEY_DEL_EOS
	.value("KEY_INS_LINE",  	GIZMO_KEY_INS_LINE)		///< GIZMO_KEY_INS_LINE
	.value("KEY_DEL_LINE",  	GIZMO_KEY_DEL_LINE)		///< GIZMO_KEY_DEL_LINE
	.value("KEY_FN",        	GIZMO_KEY_FN)			///< GIZMO_KEY_FN
	.value("KEY_FN_ESC",    	GIZMO_KEY_FN_ESC)		///< GIZMO_KEY_FN_ESC
	.value("KEY_FN_F1",     	GIZMO_KEY_FN_F1)		///< GIZMO_KEY_FN_F1
	.value("KEY_FN_F2",     	GIZMO_KEY_FN_F2)		///< GIZMO_KEY_FN_F2
	.value("KEY_FN_F3",     	GIZMO_KEY_FN_F3)		///< GIZMO_KEY_FN_F3
	.value("KEY_FN_F4",     	GIZMO_KEY_FN_F4)		///< GIZMO_KEY_FN_F4
	.value("KEY_FN_F5",     	GIZMO_KEY_FN_F5)		///< GIZMO_KEY_FN_F5
	.value("KEY_FN_F6",     	GIZMO_KEY_FN_F6)		///< GIZMO_KEY_FN_F6
	.value("KEY_FN_F7",     	GIZMO_KEY_FN_F7)		///< GIZMO_KEY_FN_F7
	.value("KEY_FN_F8",     	GIZMO_KEY_FN_F8)		///< GIZMO_KEY_FN_F8
	.value("KEY_FN_F9",     	GIZMO_KEY_FN_F9)		///< GIZMO_KEY_FN_F9
	.value("KEY_FN_F10",    	GIZMO_KEY_FN_F10)		///< GIZMO_KEY_FN_F10
	.value("KEY_FN_F11",    	GIZMO_KEY_FN_F11)		///< GIZMO_KEY_FN_F11
	.value("KEY_FN_F12",    	GIZMO_KEY_FN_F12)		///< GIZMO_KEY_FN_F12
	.value("KEY_FN_1",      	GIZMO_KEY_FN_1)			///< GIZMO_KEY_FN_1
	.value("KEY_FN_2",      	GIZMO_KEY_FN_2)			///< GIZMO_KEY_FN_2
	.value("KEY_FN_D",      	GIZMO_KEY_FN_D)			///< GIZMO_KEY_FN_D
	.value("KEY_FN_E",      	GIZMO_KEY_FN_E)			///< GIZMO_KEY_FN_E
	.value("KEY_FN_F",      	GIZMO_KEY_FN_F)			///< GIZMO_KEY_FN_F
	.value("KEY_FN_S",      	GIZMO_KEY_FN_S)			///< GIZMO_KEY_FN_S
	.value("KEY_FN_B",      	GIZMO_KEY_FN_B)			///< GIZMO_KEY_FN_B
	.value("KEY_BRL_DOT1",  	GIZMO_KEY_BRL_DOT1)		///< GIZMO_KEY_BRL_DOT1
	.value("KEY_BRL_DOT2",  	GIZMO_KEY_BRL_DOT2)		///< GIZMO_KEY_BRL_DOT2
	.value("KEY_BRL_DOT3",  	GIZMO_KEY_BRL_DOT3)		///< GIZMO_KEY_BRL_DOT3
	.value("KEY_BRL_DOT4",  	GIZMO_KEY_BRL_DOT4)		///< GIZMO_KEY_BRL_DOT4
	.value("KEY_BRL_DOT5",  	GIZMO_KEY_BRL_DOT5)		///< GIZMO_KEY_BRL_DOT5
	.value("KEY_BRL_DOT6",  	GIZMO_KEY_BRL_DOT6)		///< GIZMO_KEY_BRL_DOT6
	.value("KEY_BRL_DOT7",  	GIZMO_KEY_BRL_DOT7)		///< GIZMO_KEY_BRL_DOT7
	.value("KEY_BRL_DOT8",  	GIZMO_KEY_BRL_DOT8)		///< GIZMO_KEY_BRL_DOT8
	.value("KEY_MAX",       	GIZMO_KEY_MAX)			///< GIZMO_KEY_MAX
	;

#endif // __GizmoKeyDefPythonExposures_h

