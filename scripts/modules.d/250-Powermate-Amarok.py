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
from GizmoScriptRunningApplication import *
import subprocess

ENABLED = True
VERSION_NEEDED = 3.2
INTERESTED_CLASSES = [GizmoEventClass.Powermate]
INTERESTED_APPLICATION = "amarokapp"

############################
# PowermateAmarok Class definition
##########################

class PowermateAmarok(GizmoScriptRunningApplication):
	"""
	Amarok Powermate Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""

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
		
		GizmoScriptRunningApplication.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES, INTERESTED_APPLICATION)

############################
# PowermateAmarok class end
##########################

# register the user script
PowermateAmarok()
