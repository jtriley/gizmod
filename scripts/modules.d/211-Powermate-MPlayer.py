    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate MPlayer config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

ENABLED = True
VERSION_NEEDED = 3.0
INTERESTED_CLASSES = [GizmoEventClass.Powermate]
INTERESTED_WINDOWS = ["mplayer"]

############################
# PowermateMPlayer Class definition
##########################

class PowermateMPlayer:
	"""
	MPlayer Powermate Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event class is in INTERESTED_CLASSES and the active window is
		# one of INTERESTED_WINDOWS and there is a keyboard and mouse attached 
		# then process the event
		if Event.Class in INTERESTED_CLASSES \
		   and [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1] \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
		   	# Only interact with MPlayer if it's the first Powermate
		  	if Gizmo.DeviceClassID == 0:
			   	# Check for rotations
				if Event.Type == GizmoEventType.EV_REL:
					# scroll the window slowly if the button isn't pressed
					# and fast if the button is down
					if not Gizmo.getKeyState(GizmoKey.BTN_0):
						# scroll slowly (create a mouse wheel event)
						Gizmod.Mice[0].createEvent(GizmoEventType.EV_REL, GizmoMouseAxis.WHEEL, Event.Value)
					else:
						# scroll quickly (by pages using the page up / page down keys)
						if Event.Value < 0:
							for repeat in range(abs(Event.Value)):
								Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
						else:
							for repeat in range(abs(Event.Value)):
								Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
					return True
				elif Event.Type == GizmoEventType.EV_KEY:
					if Event.Value == 0 and not Gizmo.Rotated:
						Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
			   			return True
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
# PowermateMPlayer class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * PowermateMPlayer", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(PowermateMPlayer())
