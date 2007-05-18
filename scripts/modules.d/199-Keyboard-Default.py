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
import subprocess

ENABLED = True
VERSION_NEEDED = 3.0
INTERESTED_CLASSES = [GizmoEventClass.Standard]

############################
# KeyboardDefault Class definition
##########################

class KeyboardDefault:
	"""
	Default Fancy Keyboard Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event is not a key release and the class is in INTERESTED_CLASSES 
		# and there is a keyboard and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES and Event.Value != 0 and len(Gizmod.Mice) and len(Gizmod.Keyboards):
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
		   		# ctrl alt right (switch workspace in beryl
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PREVIOUSSONG:
		   		# ctrl alt left (switch workspace in beryl
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
		   		return True
		   	else:
		   		# unmatched event, keep processing
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
		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")

############################
# KeyboardDefault class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * KeyboardDefault", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(KeyboardDefault())
