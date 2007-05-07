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
import subprocess

ENABLED = True
USES_LIRC_REMOTES = ["Hauppauge_350"]
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_APPLICATION = "amarokapp"

############################
# LIRCHauppaugeAmarok Class definition
##########################

class LIRCHauppaugeAmarok:
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
		if Event.Class in INTERESTED_CLASSES and Event.Remote in USES_LIRC_REMOTES \
		   and Gizmod.isProcessRunning(INTERESTED_APPLICATION) >= 0 \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
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
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(LIRCHauppaugeAmarok())
