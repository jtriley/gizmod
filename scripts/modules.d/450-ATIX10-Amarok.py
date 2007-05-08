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
import subprocess

ENABLED = True
VERSION_NEEDED = 3.0
INTERESTED_CLASSES = [GizmoEventClass.ATIX10]
INTERESTED_APPLICATION = "amarokapp"

############################
# ATIX10Amarok Class definition
##########################

class ATIX10Amarok:
	"""
	Amarok ATIX10 Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event is not a key release and the class is in INTERESTED_CLASSES 
		# and there is a ATIX10 and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES and Event.Value != 0 and Gizmod.isProcessRunning(INTERESTED_APPLICATION) >= 0 \
		   and len(Gizmod.Keyboards) and len(Gizmod.Mice):
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
# ATIX10Amarok class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * ATIX10Amarok", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(ATIX10Amarok())
