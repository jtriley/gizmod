    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRCMceUSB2 MPlayer config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoScriptActiveApplication import *
import subprocess

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_WINDOWS = ["mplayer"]
USES_LIRC_REMOTES = ["mceusb", "mceusb2"]

############################
# LIRCMceUSB2MPlayer Class definition
##########################

class LIRCMceUSB2MPlayer(GizmoScriptActiveApplication):
	"""
	MPlayer LIRC Event Mapping for the MceUSB2 remote
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
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
	   		return True
	   	elif Event.Button == "TV":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_A)
	   		return True
	   	elif Event.Button == "Music":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_B)
	   		return True
	   	elif Event.Button == "Pictures":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_V)
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
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
	   		return True
	   	elif Event.Button == "Rewind":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
	   		return True
	   	elif Event.Button == "Play":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
	   		return True
	   	elif Event.Button == "Forward":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
	   		return True
	   	elif Event.Button == "Replay":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
	   		return True
	   	elif Event.Button == "Back":
	   		return False
	   	elif Event.Button == "Up":
	   		return False
	   	elif Event.Button == "Skip":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
	   		return True
	   	elif Event.Button == "More":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_O)
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
	   		return False
	   	elif Event.Button == "VolDown":
	   		return False
	   	elif Event.Button == "Home":
	   		return False
	   	elif Event.Button == "ChanUp":
	   		return False
	   	elif Event.Button == "ChanDown":
	   		return False
	   	elif Event.Button == "RecTV":
	   		return False
	   	elif Event.Button == "Mute":
	   		return False
	   	elif Event.Button == "DVD":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_N)
	   		return True
	   	elif Event.Button == "Guide":
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
	   		return True
	   	elif Event.Button == "LiveTV":
	   		return False
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
	   		return False
	   	elif Event.Button == "Enter":
	   		return False
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
		
		GizmoScriptActiveApplication.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES, INTERESTED_WINDOWS)

############################
# LIRCMceUSB2MPlayer class end
##########################

# register the user script
LIRCMceUSB2MPlayer()
