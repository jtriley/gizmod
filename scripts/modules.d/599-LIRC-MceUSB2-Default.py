    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRCMceUSB2 Default config
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
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
USES_LIRC_REMOTES = ["mceusb", "mceusb2"]

############################
# LIRCMceUSB2Default Class definition
##########################

class LIRCMceUSB2Default(GizmoScriptDefault):
	"""
	Default LIRC Event Mapping for the MceUSB2 remote
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function.
		"""
		
		# if the event isn't from the remote we're interested in don't handle it
		if Event.Remote not in USES_LIRC_REMOTES:
			return False

		# process the key
	   	if   Event.Button == "Power":
	   		return False
	   	elif Event.Button == "TV":
	   		return False
	   	elif Event.Button == "Music":
	   		return False
	   	elif Event.Button == "Pictures":
	   		subprocess.Popen(["xset", "dpms", "force", "off"])
	   		return True
	   	elif Event.Button == "Videos":
	   		return False
	   	elif Event.Button == "Stop":
	   		return False
	   	elif Event.Button == "Record":
	   		return False
	   	elif Event.Button == "Pause":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
	   		return True
	   	elif Event.Button == "Rewind":
	   		return False
	   	elif Event.Button == "Play":
	   		return False
	   	elif Event.Button == "Forward":
	   		return False
	   	elif Event.Button == "Replay":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_BACKSPACE)
	   		return True
	   	elif Event.Button == "Back":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
	   		return True
	   	elif Event.Button == "Up":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
	   		return True
	   	elif Event.Button == "Skip":
	   		return False
	   	elif Event.Button == "More":
	   		return False
	   	elif Event.Button == "Left":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
	   		return True
	   	elif Event.Button == "OK":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
	   		return True
	   	elif Event.Button == "Right":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
	   		return True
	   	elif Event.Button == "Down":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
	   		return True
	   	elif Event.Button == "VolUp":
	   		if Gizmod.DefaultMixerVolume:
	   			Gizmod.DefaultMixerVolume.VolumePlaybackPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent + 2.5
	   		return True
	   	elif Event.Button == "VolDown":
	   		if Gizmod.DefaultMixerVolume:
	   			Gizmod.DefaultMixerVolume.VolumePlaybackPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent - 2.5
	   		return True
	   	elif Event.Button == "Home":
	   		return False
	   	elif Event.Button == "ChanUp":
	   		return False
	   	elif Event.Button == "ChanDown":
	   		return False
	   	elif Event.Button == "RecTV":
	   		return False
	   	elif Event.Button == "Mute":
   			Gizmod.toggleMuteAllCards()
	   		return True
	   	elif Event.Button == "DVD":
	   		return False
	   	elif Event.Button == "Guide":
	   		return False
	   	elif Event.Button == "LiveTV":
	   		return False
	   	elif Event.Button == "One":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_1)
	   		return True
	   	elif Event.Button == "Two":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_2)
	   		return True
	   	elif Event.Button == "Three":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_3)
	   		return True
	   	elif Event.Button == "Four":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_4)
	   		return True
	   	elif Event.Button == "Five":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_5)
	   		return True
	   	elif Event.Button == "Six":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_6)
	   		return True
	   	elif Event.Button == "Seven":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_7)
	   		return True
	   	elif Event.Button == "Eight":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_8)
	   		return True
	   	elif Event.Button == "Nine":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_9)
	   		return True
	   	elif Event.Button == "Star":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_F12, [GizmoKey.KEY_LEFTMETA])
	   		return True
	   	elif Event.Button == "Zero":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_0)
	   		return True
	   	elif Event.Button == "Hash":
	   		return False
	   	elif Event.Button == "Clear":
	   		return False
	   	elif Event.Button == "Enter":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
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
# LIRCMceUSB2Default class end
##########################

# register the user script
LIRCMceUSB2Default()
