    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Keyboard Default config
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
import subprocess

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.Standard]

############################
# KeyboardDefault Class definition
##########################

class KeyboardDefault(GizmoScriptDefault):
	"""
	Default Fancy Keyboard Event Mapping
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
	   	if Event.Code == GizmoKey.KEY_EJECTCD or \
	   	   Event.Code == GizmoKey.KEY_EJECTCLOSECD:
   			subprocess.Popen(["eject", "/dev/dvd"])
   			subprocess.Popen(["eject", "/dev/cdrom"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_CLOSECD:
   			subprocess.Popen(["mount", "/media/dvd"])
   			subprocess.Popen(["mount", "/media/cdrom"])
   			subprocess.Popen(["mount", "/mnt/dvd"])
   			subprocess.Popen(["mount", "/mnt/cdrom"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_WWW:
   			subprocess.Popen(["firefox", "http://gizmod.sf.net"])
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
	   	elif Event.Code == GizmoKey.KEY_NEXTSONG:
	   		# ctrl alt right (switch workspace in compiz)
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PREVIOUSSONG:
	   		# ctrl alt left (switch workspace in compiz)
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
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
		
		GizmoScriptDefault.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES)

############################
# KeyboardDefault class end
##########################

# register the user script
KeyboardDefault()
