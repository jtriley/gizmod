    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	ATIX10 Default config
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
from GizmoScriptDefault import *
from GizmoScriptAltTabber import *
import subprocess

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.ATIX10]

############################
# ATIX10Default Class definition
##########################

class ATIX10Default(GizmoScriptDefault):
	"""
	Default ATIX10 Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# process the key
		if Event.Code == GizmoKey.BTN_LEFT:
			# do mouse left click
			Gizmod.Mice[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_BTN_LFT, Event.Value)
			return True
		elif Event.Code == GizmoKey.BTN_RIGHT:
			# do mouse right click
			Gizmod.Mice[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_BTN_RIGHT, Event.Value)
			return True
		elif Event.Type == GizmoEventType.EV_REL:
			# do mouse movements
			Gizmod.Mice[0].createEventRaw(GizmoEventType.EV_REL, Event.Code, Event.Value)
			return True
		elif Event.Value != 0:
			# do button presses
		   	if Event.Code == GizmoKey.KEY_WWW:
	   			subprocess.Popen(["firefox", "http://gizmod.sf.net"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_BOOKMARKS:
		   		self.AltTabber.doAltTab()
		   		return True
		   	elif Event.Code == GizmoKey.KEY_VOLUMEUP:
	   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback + 1
		   		return True
		   	elif Event.Code == GizmoKey.KEY_VOLUMEDOWN:
	   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback - 1
		   		return True
		   	elif Event.Code == GizmoKey.KEY_MUTE:
	   			Gizmod.toggleMuteAllCards()
		   		return True
		   	elif Event.Code == GizmoKey.KEY_LEFT:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_RIGHT:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_UP:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_DOWN:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_ENTER:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_OK:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_1:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_1)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_2:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_2)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_3:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_3)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_4:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_4)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_5:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_5)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_6:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_6)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_7:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_7)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_8:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_8)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_9:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_9)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_0:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_0)
		   		return True
		   	else:
		   		# Event not mappped
				return False
		# event not of interest
		return False
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptDefault.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES)
		self.AltTabber = GizmoScriptAltTabber()

############################
# ATIX10Default class end
##########################

# register the user script
ATIX10Default()
