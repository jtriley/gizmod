    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate Default config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
import time

ENABLED = True
VERSION_NEEDED = 3.0
INTERESTED_CLASSES = [GizmoEventClass.Powermate]

############################
# PowermateDefault Class definition
##########################

class PowermateDefault:
	"""
	Default Powermate Event Mapping
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
		   	# Check for rotations
			if Event.Type == GizmoEventType.EV_REL:
				if not Gizmo.getKeyState(GizmoKey.BTN_0):
			   		if Gizmod.DefaultMixerVolume:
			   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback + Event.Value
				else:
					# scroll quickly (by pages using the page up / page down keys)
					if Event.Value < 0:
						for repeat in range(abs(Event.Value)):
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
					else:
						for repeat in range(abs(Event.Value)):
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT, [GizmoKey.KEY_LEFTCTRL, GizmoKey.KEY_LEFTALT])
				return True
			elif Event.Type == GizmoEventType.EV_KEY:
				if Event.Value == 0 and not Gizmo.Rotated:
					Gizmod.toggleMuteAllCards()
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
# PowermateDefault class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * PowermateDefault", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(PowermateDefault())
