    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Keyboard Amarok config
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
from GizmoScriptRunningApplication import *
import subprocess

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.Standard]
INTERESTED_APPLICATION = "amarokapp"

############################
# KeyboardAmarok Class definition
##########################

class KeyboardAmarok(GizmoScriptRunningApplication):
	"""
	Amarok Fancy Keyboard Event Mapping
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
	   	if Event.Code == GizmoKey.KEY_VOLUMEUP:
   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback + 1
	   		return True
	   	elif Event.Code == GizmoKey.KEY_VOLUMEDOWN:
   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback - 1
	   		return True
	   	elif Event.Code == GizmoKey.KEY_MUTE:
   			Gizmod.toggleMuteAllCards()
	   		return True
	   	elif Event.Code == GizmoKey.KEY_NEXTSONG:
   			subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_NEXT:
   			subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_STOP:
   			subprocess.Popen(["amarok", "--stop"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PREVIOUSSONG:
   			subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PREVIOUS:
   			subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PAUSE:
   			subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PLAYPAUSE:
   			subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PAUSECD:
   			subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PLAY:
   			subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PLAYCD:
   			subprocess.Popen(["amarok", "--play-pause"])
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
		
		GizmoScriptRunningApplication.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES, INTERESTED_APPLICATION)

############################
# KeyboardAmarok class end
##########################

# register the user script
KeyboardAmarok()
