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
