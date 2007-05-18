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
	   		# ctrl alt right (switch workspace in beryl)
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PREVIOUSSONG:
	   		# ctrl alt left (switch workspace in beryl)
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
