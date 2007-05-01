    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	Powermate Default config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

INTERESTED_CLASSES = [GizmoEventClass.Powermate]
ENABLED = True

############################
# PowermateDefault Class definition
##########################

class PowermateDefault:
	"""
	Default Event mapping for the Powermate
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
					if Event.Value > 0:
						for repeat in range(abs(Event.Value)):
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 1)
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 1)
							Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 0)
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 0)
					else:
						for repeat in range(abs(Event.Value)):
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 1)
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 1)
							Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 0)
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 0)
				return True
			elif Event.Type == GizmoEventType.EV_KEY:
				if Event.Value == 1:
					Gizmod.toggleMuteAllCards()
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
# PowermateDefault class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(PowermateDefault())
