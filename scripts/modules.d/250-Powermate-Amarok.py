    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate Amarok config
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
VERSION_NEEDED = 3.0
INTERESTED_CLASSES = [GizmoEventClass.Powermate]
INTERESTED_APPLICATION = "amarokapp"

############################
# PowermateAmarok Class definition
##########################

class PowermateAmarok:
	"""
	Amarok Powermate Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""

		# if the event class is in INTERESTED_CLASSES and Amarok is running and there 
		# is a keyboard and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES and Gizmod.isProcessRunning(INTERESTED_APPLICATION) >= 0 \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
		   	# Only interact with Amarok if it's the first Powermate
		  	if Gizmo.DeviceClassID == 0:
			   	# Check for rotations
				if Event.Type == GizmoEventType.EV_REL:
					if Gizmo.getKeyState(GizmoKey.BTN_0):
						# scroll quickly (by pages using the page up / page down keys)
						if Event.Value > 0:
							for repeat in range(abs(Event.Value)):
					   			subprocess.Popen(["amarok", "--previous"])
						else:
							for repeat in range(abs(Event.Value)):
					   			subprocess.Popen(["amarok", "--next"])
						return True
				elif Event.Type == GizmoEventType.EV_KEY:
					if Event.Value == 0 and not Gizmo.Rotated:
			   			subprocess.Popen(["amarok", "--play-pause"])
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
# PowermateAmarok class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * PowermateAmarok", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(PowermateAmarok())
