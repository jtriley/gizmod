    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	ATIX10 Amarok config
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
INTERESTED_CLASSES = [GizmoEventClass.ATIX10]
INTERESTED_APPLICATION = "amarokapp"

############################
# ATIX10Amarok Class definition
##########################

class ATIX10Amarok(GizmoScriptRunningApplication):
	"""
	Amarok ATIX10 Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# ensure only one event per button press		
		if Event.Value == 0:
			return False
			
		# process the key
	   	if Event.Code == GizmoKey.KEY_PAUSE:
		   	subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_PLAY:
		   	subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_STOP:
		   	subprocess.Popen(["amarok", "--stop"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_LEFT:
		   	subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_REWIND:
		   	subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_RIGHT:
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Code == GizmoKey.KEY_FORWARD:
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
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
		
		GizmoScriptRunningApplication.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES, INTERESTED_APPLICATION)

############################
# ATIX10Amarok class end
##########################

# register the user script
ATIX10Amarok()
