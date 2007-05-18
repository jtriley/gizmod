    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate Firefox config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoScriptActiveApplication import *

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.Powermate]
INTERESTED_WINDOWS = ["firefox"]

############################
# PowermateFirefox Class definition
##########################

class PowermateFirefox(GizmoScriptActiveApplication):
	"""
	Firefox Powermate Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
	   	# Only interact with Firefox if it's the first Powermate
	  	if Gizmo.DeviceClassID == 0:
		   	# Check for rotations
			if Event.Type == GizmoEventType.EV_REL:
				# scroll the window slowly if the button isn't pressed
				# and fast if the button is down
				if not Gizmo.getKeyState(GizmoKey.BTN_0):
					# scroll slowly (create a mouse wheel event)
					Gizmod.Mice[0].createEvent(GizmoEventType.EV_REL, GizmoMouseAxis.WHEEL, -Event.Value)
				else:
					# scroll quickly (by pages using the page up / page down keys)
					if Event.Value > 0:
						for repeat in range(abs(Event.Value)):
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
					else:
						for repeat in range(abs(Event.Value)):
							Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
				return True
			else:
				return False
		else:
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
# PowermateFirefox class end
##########################

# register the user script
PowermateFirefox()
