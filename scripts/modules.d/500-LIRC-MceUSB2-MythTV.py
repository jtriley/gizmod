    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	LIRCMceUSB2 MythTV config
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
USES_LIRC_REMOTES = ["mceusb", "mceusb2"]
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_WINDOWS = ["mythfrontend"]
POWER_APPLICATION = "mythfrontend"

############################
# LIRCMceUSB2MythTV Class definition
##########################

class LIRCMceUSB2MythTV:
	"""
	MythTV LIRC Event Mapping for the MceUSB2 remote
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# check for power button
		# if pressed and mythfrontend isn't running, then launch it
		# also return False so that other scripts may make use of the power
		# button as well
		if Event.Class in INTERESTED_CLASSES \
		   and Event.Remote in USES_LIRC_REMOTES \
		   and Event.Button == "Power" \
		   and Gizmod.isProcessRunning(POWER_APPLICATION) < 0:
   			subprocess.Popen([POWER_APPLICATION])
   			Gizmod.updateProcessTree() # force an instantaneous process tree update
	   		return False

		# if the event class is in INTERESTED_CLASSES and the active window is
		# one of INTERESTED_WINDOWS and there is a keyboard and mouse attached 
		# then process the event
		if Event.Class in INTERESTED_CLASSES and Event.Remote in USES_LIRC_REMOTES \
		   and [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1] \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	if   Event.Button == "Power":
		   		# if mythfrontend is open, kill it
	   			subprocess.Popen(["killall", "mythfrontend"])
		   		return True
		   	elif Event.Button == "TV":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_A)
		   		return True
		   	elif Event.Button == "Music":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_B)
		   		return True
		   	elif Event.Button == "Pictures":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH)
		   		return True
		   	elif Event.Button == "Videos":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
		   		return True
		   	elif Event.Button == "Stop":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
		   		return True
		   	elif Event.Button == "Record":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_R)
		   		return True
		   	elif Event.Button == "Pause":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
		   		return True
		   	elif Event.Button == "Rewind":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_COMMA)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
		   		return True
		   	elif Event.Button == "Play":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
		   		return True
		   	elif Event.Button == "Forward":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_DOT)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
		   		return True
		   	elif Event.Button == "Replay":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
		   		return True
		   	elif Event.Button == "Back":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
		   		return True
		   	elif Event.Button == "Up":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
		   		return True
		   	elif Event.Button == "Skip":
		   		return False
		   	elif Event.Button == "More":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_M)
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
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTBRACE)
		   		return True
		   	elif Event.Button == "VolDown":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTBRACE)
		   		return True
		   	elif Event.Button == "Home":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_END)
		   		return True
		   	elif Event.Button == "ChanUp":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
		   		return True
		   	elif Event.Button == "ChanDown":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
		   		return True
		   	elif Event.Button == "RecTV":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_HOME)
		   		return True
		   	elif Event.Button == "Mute":
		   		return False
		   	elif Event.Button == "DVD":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_H)
		   		return True
		   	elif Event.Button == "Guide":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
		   		return True
		   	elif Event.Button == "LiveTV":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_N)
		   		return True
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
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_C)
		   		return True
		   	elif Event.Button == "Enter":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_I)
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
# LIRCMceUSB2MythTV class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(LIRCMceUSB2MythTV())
