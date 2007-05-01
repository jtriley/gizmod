    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
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
INTERESTED_CLASSES = [GizmoEventClass.Standard]

############################
# KeyboardDefault Class definition
##########################

class KeyboardDefault:
	"""
	Default event mapping for fancy keyboards 
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event class is in INTERESTED_CLASSES and there 
		# is a keyboard and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	if Event.Code == GizmoKey.KEY_EJECTCD or \
		   	   Event.Code == GizmoKey.KEY_EJECTCLOSECD:
	   			subprocess.Popen(["eject", "/dev/dvd"])
	   			subprocess.Popen(["eject", "/dev/cdrom"])
		   		return True
		   	if Event.Code == GizmoKey.KEY_CLOSECD:
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
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 0)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 0)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PREVIOUSSONG:
		   		# ctrl alt left (switch workspace in beryl
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 0)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 0)
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
		
		print "Loaded User Script: " + self.__class__.__name__

############################
# KeyboardDefault class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(KeyboardDefault())
