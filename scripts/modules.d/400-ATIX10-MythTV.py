    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	ATIX10 MythTV config
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
INTERESTED_CLASSES = [GizmoEventClass.ATIX10]
INTERESTED_WINDOWS = ["mythfrontend"]
POWER_APPLICATION = "mythfrontend"

############################
# ATIX10MythTV Class definition
##########################

class ATIX10MythTV(GizmoScriptActiveApplication):
	"""
	MythTV ATIX10 Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# emsire only one event per button
	   	if Event.Value == 0:
	   		return False
	   		
		# process the key
	   	if Event.Code == GizmoKey.KEY_POWER:
	   		# if mythfrontend is open, kill it
   			subprocess.Popen(["killall", "mythfrontend"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_A:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_A)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_B:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_B)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PROG1:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PROG2:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_WWW:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_V)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_BOOKMARKS:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_N)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_EDIT:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_I)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_VOLUMEUP:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTBRACE)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_VOLUMEDOWN:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTBRACE)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_CHANNELUP:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_CHANNELDOWN:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_MENU:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_M)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_KPENTER:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_END)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_C:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_C)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_D:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_D)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_COFFEE:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_FRONT:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_HOME)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_E:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_H)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_F:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_M)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_REWIND:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_COMMA, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PLAYCD:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_FORWARD:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOT, [GizmoKey.KEY_RIGHTSHIFT])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_RECORD:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_R)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_STOP:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PAUSE:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
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
		if Event.Class in INTERESTED_CLASSES \
	   	   and Event.Value != 0 \
		   and Event.Code == GizmoKey.KEY_POWER \
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
# ATIX10MythTV class end
##########################

# register the user script
ATIX10MythTV()
