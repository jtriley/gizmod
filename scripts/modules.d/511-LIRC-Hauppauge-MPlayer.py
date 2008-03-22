    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRCHauppauge MPlayer config
#***
#*****************************************
  #*****************************************
    #***

"""

  Copyright (c) 2007, Gizmo Daemon Team
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
"""

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoScriptActiveApplication import *
import subprocess
import sys

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_WINDOWS = ["mplayer"]
USES_LIRC_REMOTES = ["Hauppauge_350"]

############################
# LIRCHauppaugeMPlayer Class definition
##########################

class LIRCHauppaugeMPlayer(GizmoScriptActiveApplication):
	"""
	MPlayer LIRC Event Mapping for the Hauppauge remote
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event isn't from the remote we're interested in don't handle it
		if Event.Remote not in USES_LIRC_REMOTES:
			return False

		# process the key
	   	if   Event.Button == "Go":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_A)
	   		return True
	   	elif Event.Button == "Power":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
	   		return True
	   	elif Event.Button == "TV":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_B)
	   		return True
	   	elif Event.Button == "Videos":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_V)
	   		return True
	   	elif Event.Button == "Music":		   	
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Button == "Pictures":
	   		return False
	   	elif Event.Button == "Guide":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
	   		return True
	   	elif Event.Button == "Up":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
	   		return True
	   	elif Event.Button == "Radio":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_N)
	   		return True
	   	elif Event.Button == "Left":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
	   		return True
	   	elif Event.Button == "OK":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
	   		return True
	   	elif Event.Button == "Right":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
	   		return True
	   	elif Event.Button == "Back/Exit":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
	   		return True
	   	elif Event.Button == "Down":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
	   		return True
	   	elif Event.Button == "Menu/i":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_O)
	   		return True
		elif Event.Button == "Vol+":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_0)
			return True
	   	elif Event.Button == "Vol-":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_9)
			return True		
	   	elif Event.Button == "Prev.Ch":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_H)
	   		return True
	   	elif Event.Button == "Mute":
	   		return False
	   	elif Event.Button == "Ch+":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
	   		return True
	   	elif Event.Button == "Ch-":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
	   		return True
	   	elif Event.Button == "Record":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_R)
	   		return True
	   	elif Event.Button == "Stop":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
	   		return True
	   	elif Event.Button == "Rewind":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_COMMA, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Button == "Play":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
	   		return True
	   	elif Event.Button == "Forward":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOT, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Button == "Replay/SkipBackward":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
	   		return True
	   	elif Event.Button == "Pause":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
	   		return True
	   	elif Event.Button == "SkipForward":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
	   		return True
	   	elif Event.Button == "1":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_1)
	   		return True
	   	elif Event.Button == "2":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_2)
	   		return True
	   	elif Event.Button == "3":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_3)
	   		return True
	   	elif Event.Button == "4":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_4)
	   		return True
	   	elif Event.Button == "5":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_5)
	   		return True
	   	elif Event.Button == "6":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_6)
	   		return True
	   	elif Event.Button == "7":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_7)
	   		return True
	   	elif Event.Button == "8":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_8)
	   		return True
	   	elif Event.Button == "9":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_9)
	   		return True
	   	elif Event.Button == "Asterix":
	   		return False
	   	elif Event.Button == "0":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_0)
	   		return True
	   	elif Event.Button == "#":
	   		return False
	   	elif Event.Button == "Red":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_END)
	   		return True
	   	elif Event.Button == "Green":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_HOME)
	   		return True
	   	elif Event.Button == "Yellow":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_C)
	   		return True
	   	elif Event.Button == "Blue":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_I)
	   		return True
	   	else:
	   		# unmatched event, keep processing
			return False				
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptActiveApplication.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES, INTERESTED_WINDOWS)

############################
# LIRCHauppaugeMPlayer class end
##########################

# register the user script
LIRCHauppaugeMPlayer()
