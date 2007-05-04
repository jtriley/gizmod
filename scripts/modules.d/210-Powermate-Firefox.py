    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	Powermate Firefox config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

ENABLED = True
INTERESTED_CLASSES = [GizmoEventClass.Powermate]
INTERESTED_WINDOWS = ["firefox"]

############################
# PowermateFirefox Class definition
##########################

class PowermateFirefox:
	"""
	Firefox Powermate Event Mapping
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
								Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
						else:
							for repeat in range(abs(Event.Value)):
								Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
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
# PowermateFirefox class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(PowermateFirefox())
