    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRC Hauppauge Amarok config
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
USES_LIRC_REMOTES = ["Hauppauge_350"]

############################
# LIRCHauppaugeAmarok Class definition
##########################

class LIRCHauppaugeAmarok(GizmoScriptRunningApplication):
	"""
	Amarok LIRC Hauppauge Event Mapping
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
	   	if   Event.Button == "Go":
	   		return False
	   	elif Event.Button == "Power":
	   		return False
	   	elif Event.Button == "TV":
	   		return False
	   	elif Event.Button == "Videos":
	   		return False
	   	elif Event.Button == "Music":		   	
	   		return False
	   	elif Event.Button == "Pictures":
	   		return False
	   	elif Event.Button == "Guide":
	   		return False
	   	elif Event.Button == "Up":
	   		return False
	   	elif Event.Button == "Radio":
	   		return False
	   	elif Event.Button == "Left":
		   	subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Button == "OK":
	   		return False
	   	elif Event.Button == "Right":
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Button == "Back/Exit":
	   		return False
	   	elif Event.Button == "Down":
	   		return False
	   	elif Event.Button == "Menu/i":
	   		return False
	   	elif Event.Button == "Vol+":
	   		return False
	   	elif Event.Button == "Vol-":
	   		return False
	   	elif Event.Button == "Prev.Ch":
	   		return False
	   	elif Event.Button == "Mute":
	   		return False
	   	elif Event.Button == "Ch+":
	   		return False
	   	elif Event.Button == "Ch-":
	   		return False
	   	elif Event.Button == "Record":
	   		return False
	   	elif Event.Button == "Stop":
		   	subprocess.Popen(["amarok", "--stop"])
	   		return True
	   	elif Event.Button == "Rewind":
	   		return False
	   	elif Event.Button == "Play":
		   	subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Button == "Forward":
	   		return False
	   	elif Event.Button == "Replay/SkipBackward":
		   	subprocess.Popen(["amarok", "--previous"])
	   		return True
	   	elif Event.Button == "Pause":
		   	subprocess.Popen(["amarok", "--play-pause"])
	   		return True
	   	elif Event.Button == "SkipForward":
		   	subprocess.Popen(["amarok", "--next"])
	   		return True
	   	elif Event.Button == "1":
	   		return False
	   	elif Event.Button == "2":
	   		return False
	   	elif Event.Button == "3":
	   		return False
	   	elif Event.Button == "4":
	   		return False
	   	elif Event.Button == "5":
	   		return False
	   	elif Event.Button == "6":
	   		return False
	   	elif Event.Button == "7":
	   		return False
	   	elif Event.Button == "8":
	   		return False
	   	elif Event.Button == "9":
	   		return False
	   	elif Event.Button == "Asterix":
	   		return False
	   	elif Event.Button == "0":
	   		return False
	   	elif Event.Button == "#":
	   		return False
	   	elif Event.Button == "Red":
	   		return False
	   	elif Event.Button == "Green":
	   		return False
	   	elif Event.Button == "Yellow":
	   		return False
	   	elif Event.Button == "Blue":
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
# LIRCHauppaugeAmarok class end
##########################

# register the user script
LIRCHauppaugeAmarok()
