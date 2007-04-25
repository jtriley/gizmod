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

INTERESTED_CLASSES = [GizmoEventClass.Powermate]
INTERESTED_WINDOWS = ["firefox"]

############################
# PowermateFirefox Class definition
##########################

class PowermateFirefox:
	"""
	Event mapping for the Powermate when using Firefox
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		if Event.Class in INTERESTED_CLASSES and \
		   [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1]:
		   	# Check for rotations
			if Event.Type == GizmoEventType.EV_REL:
				# scroll the window
				if not Gizmo.getKeyState(GizmoKey.BTN_0):
					# scroll slowly
					print "Scroll slow"
				else:
					# scroll by pages
					print "Scroll fast"
				return True

		return False
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		print "Registered User Script: " + self.__class__.__name__

############################
# PowermateFirefox class end
##########################

# register the user script
Gizmod.Dispatcher.userScripts.append(PowermateFirefox())
