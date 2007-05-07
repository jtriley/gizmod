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
		   	if   Button.Code == "Go":
		   		return False
		   	elif Button.Code == "Power":
		   		return False
		   	elif Button.Code == "TV":
		   		return False
		   	elif Button.Code == "Videos":
		   		return False
		   	elif Button.Code == "Music":		   	
		   		return False
		   	elif Button.Code == "Pictures":
		   		return False
		   	elif Button.Code == "Guide":
		   		return False
		   	elif Button.Code == "Up":
		   		return False
		   	elif Button.Code == "Radio":
		   		return False
		   	elif Button.Code == "Left":
			   	subprocess.Popen(["amarok", "--previous"])
		   		return True
		   	elif Button.Code == "OK":
		   		return False
		   	elif Button.Code == "Right":
			   	subprocess.Popen(["amarok", "--next"])
		   		return True
		   	elif Button.Code == "Back/Exit":
		   		return False
		   	elif Button.Code == "Down":
		   		return False
		   	elif Button.Code == "Menu/i":
		   		return False
		   	elif Button.Code == "Vol+":
		   		return False
		   	elif Button.Code == "Vol-":
		   		return False
		   	elif Button.Code == "Prev.Ch":
		   		return False
		   	elif Button.Code == "Mute":
		   		return False
		   	elif Button.Code == "Ch+":
		   		return False
		   	elif Button.Code == "Ch-":
		   		return False
		   	elif Button.Code == "Record":
		   		return False
		   	elif Button.Code == "Stop":
			   	subprocess.Popen(["amarok", "--stop"])
		   		return True
		   	elif Button.Code == "Rewind":
		   		return False
		   	elif Button.Code == "Play":
			   	subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif Button.Code == "Forward":
		   		return False
		   	elif Button.Code == "Replay/SkipBackward":
			   	subprocess.Popen(["amarok", "--previous"])
		   		return True
		   	elif Button.Code == "Pause":
			   	subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif Button.Code == "SkipForward":
			   	subprocess.Popen(["amarok", "--next"])
		   		return True
		   	elif Button.Code == "1":
		   		return False
		   	elif Button.Code == "2":
		   		return False
		   	elif Button.Code == "3":
		   		return False
		   	elif Button.Code == "4":
		   		return False
		   	elif Button.Code == "5":
		   		return False
		   	elif Button.Code == "6":
		   		return False
		   	elif Button.Code == "7":
		   		return False
		   	elif Button.Code == "8":
		   		return False
		   	elif Button.Code == "9":
		   		return False
		   	elif Button.Code == "Asterix":
		   		return False
		   	elif Button.Code == "0":
		   		return False
		   	elif Button.Code == "#":
		   		return False
		   	elif Button.Code == "Red":
		   		return False
		   	elif Button.Code == "Green":
		   		return False
		   	elif Button.Code == "Yellow":
		   		return False
		   	elif Button.Code == "Blue":
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
