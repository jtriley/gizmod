    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRCMceUSB2 Amarok config
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
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_APPLICATION = "amarokapp"
USES_LIRC_REMOTES = ["mceusb", "mceusb2"]

############################
# LIRCMceUSB2Amarok Class definition
##########################

class LIRCMceUSB2Amarok(GizmoScriptRunningApplication):
	"""
	Amarok LIRC Event Mapping for the MceUSB2 remote
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""

		# if the event isn't from the remote we're interested in don't handle it				
		if Event.Remote not in USES_LIRC_REMOTES:
			return False
			
		# process the key
	   	if   Event.Button == "Power":
	   		return False
	   	elif Event.Button == "TV":
	   		return False
	   	elif Event.Button == "Music":
	   		return False
	   	elif Event.Button == "Pictures":
	   		return False
	   	elif Event.Button == "Videos":
	   		return False
	   	elif Event.Button == "Stop":
		   	subprocess.Popen(["amarok", "--stop"])
	   		return True
	   	elif Event.Button == "Record":
	   		return False
	   	elif Event.Button == "Pause":
		   	subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Button == "Rewind":
		   	subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Button == "Play":
		   	subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Button == "Forward":
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Button == "Replay":
		   	subprocess.Popen(["amarok", "--stop"])
		   	subprocess.Popen(["amarok", "--play"])
	   		return True
	   	elif Event.Button == "Back":
	   		return False
	   	elif Event.Button == "Up":
	   		return False
	   	elif Event.Button == "Skip":
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Button == "More":
	   		return False
	   	elif Event.Button == "Left":
		   	subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Button == "OK":
	   		return False
	   	elif Event.Button == "Right":
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Button == "Down":
	   		return False
	   	elif Event.Button == "VolUp":
	   		return False
	   	elif Event.Button == "VolDown":
	   		return False
	   	elif Event.Button == "Home":
	   		return False
	   	elif Event.Button == "ChanUp":
	   		return False
	   	elif Event.Button == "ChanDown":
	   		return False
	   	elif Event.Button == "RecTV":
	   		return False
	   	elif Event.Button == "Mute":
	   		return False
	   	elif Event.Button == "DVD":
	   		return False
	   	elif Event.Button == "Guide":
	   		return False
	   	elif Event.Button == "LiveTV":
	   		return False
	   	elif Event.Button == "One":
	   		return False
	   	elif Event.Button == "Two":
	   		return False
	   	elif Event.Button == "Three":
	   		return False
	   	elif Event.Button == "Four":
	   		return False
	   	elif Event.Button == "Five":
	   		return False
	   	elif Event.Button == "Six":
	   		return False
	   	elif Event.Button == "Seven":
	   		return False
	   	elif Event.Button == "Eight":
	   		return False
	   	elif Event.Button == "Nine":
	   		return False
	   	elif Event.Button == "Star":
	   		return False
	   	elif Event.Button == "Zero":
	   		return False
	   	elif Event.Button == "Hash":
	   		return False
	   	elif Event.Button == "Clear":
	   		return False
	   	elif Event.Button == "Enter":
	   		return False
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
# LIRCMceUSB2Amarok class end
##########################

# register the user script
LIRCMceUSB2Amarok()
