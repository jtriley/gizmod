    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	LIRC Hauppauge Amarok config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoDeviceStrings import *
from Hauppauge import *
import subprocess

ENABLED = True
USES_LIRC_REMOTE = "Hauppauge"
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_APPLICATION = "amarokapp"

############################
# LIRCHauppaugeAmarok Class definition
##########################

class LIRCHauppaugeAmarok(Hauppauge):
	"""
	Amarok LIRC Hauppauge Event Mapping
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
		if Event.Class in INTERESTED_CLASSES and Gizmod.isProcessRunning(INTERESTED_APPLICATION) >= 0 \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	KeyString = self.getKeyString(Event)
		   	if not KeyString:
		   		return False
		   	elif KeyString == "Go":
		   		return False
		   	elif KeyString == "Power":
		   		return False
		   	elif KeyString == "TV":
		   		return False
		   	elif KeyString == "Videos":
		   		return False
		   	elif KeyString == "Music":		   	
		   		return False
		   	elif KeyString == "Pictures":
		   		return False
		   	elif KeyString == "Guide":
		   		return False
		   	elif KeyString == "Up":
		   		return False
		   	elif KeyString == "Radio":
		   		return False
		   	elif KeyString == "Left":
			   	subprocess.Popen(["amarok", "--previous"])
		   		return True
		   	elif KeyString == "OK":
		   		return False
		   	elif KeyString == "Right":
			   	subprocess.Popen(["amarok", "--next"])
		   		return True
		   	elif KeyString == "Back/Exit":
		   		return False
		   	elif KeyString == "Down":
		   		return False
		   	elif KeyString == "Menu":
		   		return False
		   	elif KeyString == "VolUp":
		   		return False
		   	elif KeyString == "VolDown":
		   		return False
		   	elif KeyString == "Prev.Ch":
		   		return False
		   	elif KeyString == "Mute":
		   		return False
		   	elif KeyString == "ChUp":
		   		return False
		   	elif KeyString == "ChDown":
		   		return False
		   	elif KeyString == "Rec":
		   		return False
		   	elif KeyString == "Stop":
			   	subprocess.Popen(["amarok", "--stop"])
		   		return True
		   	elif KeyString == "Rewind":
		   		return False
		   	elif KeyString == "Play":
			   	subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif KeyString == "FastForward":
		   		return False
		   	elif KeyString == "Replay":
			   	subprocess.Popen(["amarok", "--previous"])
		   		return True
		   	elif KeyString == "Pause":
			   	subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif KeyString == "Skip":
			   	subprocess.Popen(["amarok", "--next"])
		   		return True
		   	elif KeyString == "1":
		   		return False
		   	elif KeyString == "2":
		   		return False
		   	elif KeyString == "3":
		   		return False
		   	elif KeyString == "4":
		   		return False
		   	elif KeyString == "5":
		   		return False
		   	elif KeyString == "6":
		   		return False
		   	elif KeyString == "7":
		   		return False
		   	elif KeyString == "8":
		   		return False
		   	elif KeyString == "9":
		   		return False
		   	elif KeyString == "*":
		   		return False
		   	elif KeyString == "0":
		   		return False
		   	elif KeyString == "#":
		   		return False
		   	elif KeyString == "Red":
		   		return False
		   	elif KeyString == "Green":
		   		return False
		   	elif KeyString == "Yellow":
		   		return False
		   	elif KeyString == "Blue":
		   		return False
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
# LIRCHauppaugeAmarok class end
##########################

# register the user script
if ENABLED and USES_LIRC_REMOTE in LIRC_REMOTES:
	Gizmod.Dispatcher.userScripts.append(LIRCHauppaugeAmarok())
