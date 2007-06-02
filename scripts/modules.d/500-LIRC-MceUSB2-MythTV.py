    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRCMceUSB2 MythTV config
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

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_WINDOWS = ["mythfrontend"]
USES_LIRC_REMOTES = ["mceusb", "mceusb2"]
POWER_APPLICATION = "mythfrontend"

############################
# LIRCMceUSB2MythTV Class definition
##########################

class LIRCMceUSB2MythTV(GizmoScriptActiveApplication):
	"""
	MythTV LIRC Event Mapping for the MceUSB2 remote
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
	   	if   Event.Button == "Power":
	   		# if mythfrontend is open, kill it
   			subprocess.Popen(["killall", "mythfrontend"])
	   		return True
	   	elif Event.Button == "TV":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_A)
	   		return True
	   	elif Event.Button == "Music":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_B)
	   		return True
	   	elif Event.Button == "Pictures":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH)
	   		return True
	   	elif Event.Button == "Videos":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Button == "Stop":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
	   		return True
	   	elif Event.Button == "Record":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_R)
	   		return True
	   	elif Event.Button == "Pause":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
	   		return True
	   	elif Event.Button == "Rewind":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_COMMA, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Button == "Play":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
	   		return True
	   	elif Event.Button == "Forward":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOT, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Button == "Replay":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
	   		return True
	   	elif Event.Button == "Back":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
	   		return True
	   	elif Event.Button == "Up":
	   		return False
	   	elif Event.Button == "Skip":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
	   		return True
	   	elif Event.Button == "More":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_M)
	   		return True
	   	elif Event.Button == "Left":
	   		return False
	   	elif Event.Button == "OK":
	   		return False
	   	elif Event.Button == "Right":
	   		return False
	   	elif Event.Button == "Down":
	   		return False
	   	elif Event.Button == "VolUp":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTBRACE)
	   		return True
	   	elif Event.Button == "VolDown":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTBRACE)
	   		return True
	   	elif Event.Button == "Home":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_END)
	   		return True
	   	elif Event.Button == "ChanUp":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
	   		return True
	   	elif Event.Button == "ChanDown":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
	   		return True
	   	elif Event.Button == "RecTV":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_HOME)
	   		return True
	   	elif Event.Button == "Mute":
	   		return False
	   	elif Event.Button == "DVD":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_H)
	   		return True
	   	elif Event.Button == "Guide":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
	   		return True
	   	elif Event.Button == "LiveTV":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_N)
	   		return True
	   	elif Event.Button == "One":
	   		return False
	   	elif Event.Button == "Two":
	   		return False
	   	elif Event.Button == "Three":
	   		return False
	   	elif Event.Button == "Four":
	   		return False
	   	elif Event.Button == "Five":
	   		return False
	   	elif Event.Button == "Six":
	   		return False
	   	elif Event.Button == "Seven":
	   		return False
	   	elif Event.Button == "Eight":
	   		return False
	   	elif Event.Button == "Nine":
	   		return False
	   	elif Event.Button == "Star":
	   		return False
	   	elif Event.Button == "Zero":
	   		return False
	   	elif Event.Button == "Hash":
	   		return False
	   	elif Event.Button == "Clear":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_C)
	   		return True
	   	elif Event.Button == "Enter":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_I)
	   		return True
	   	else:
	   		# unmatched event, keep processing
			return False				
	
	def onEvent(self, Event, Gizmo = None):
		"""
		Overloading Base Class' onEvent method!
		Make sure to call it!
		"""
		
		# check for power button
		# if pressed and mythfrontend isn't running, then launch it
		# also return False so that other scripts may make use of the power
		# button as well
		if Event.Class in self.InterestedClasses \
		   and Event.Remote in USES_LIRC_REMOTES \
		   and Event.Button == "Power" \
		   and Gizmod.isProcessRunning(POWER_APPLICATION) < 0:
   			subprocess.Popen([POWER_APPLICATION])
   			Gizmod.updateProcessTree() # force an instantaneous process tree update
	   		return False

		# call base classe' onEvent method
		GizmoScriptActiveApplication.onEvent(self, Event, Gizmo)
		
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptActiveApplication.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES, INTERESTED_WINDOWS)

############################
# LIRCMceUSB2MythTV class end
##########################

# register the user script
LIRCMceUSB2MythTV()
