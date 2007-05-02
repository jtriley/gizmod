    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	Keyboard Amarok config
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
INTERESTED_CLASSES = [GizmoEventClass.Standard]
INTERESTED_APPLICATION = "amarokapp"

############################
# KeyboardAmarok Class definition
##########################

class KeyboardAmarok:
	"""
	Amarok Fancy Keyboard Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event is not a key release and the class is in INTERESTED_CLASSES 
		# and amarok is running and there is a keyboard and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES and Event.Value != 0 and Gizmod.isProcessRunning(INTERESTED_APPLICATION) >= 0 \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	if Event.Code == GizmoKey.KEY_VOLUMEUP:
	   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback + 1
		   		return True
		   	elif Event.Code == GizmoKey.KEY_VOLUMEDOWN:
	   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback - 1
		   		return True
		   	elif Event.Code == GizmoKey.KEY_MUTE:
	   			Gizmod.toggleMuteAllCards()
		   		return True
		   	elif Event.Code == GizmoKey.KEY_NEXTSONG:
	   			subprocess.Popen(["amarok", "--next"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_NEXT:
	   			subprocess.Popen(["amarok", "--next"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_STOP:
	   			subprocess.Popen(["amarok", "--stop"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PREVIOUSSONG:
	   			subprocess.Popen(["amarok", "--previous"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PREVIOUS:
	   			subprocess.Popen(["amarok", "--previous"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PAUSE:
	   			subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PLAYPAUSE:
	   			subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PAUSECD:
	   			subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PLAY:
	   			subprocess.Popen(["amarok", "--play-pause"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PLAYCD:
	   			subprocess.Popen(["amarok", "--play-pause"])
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
# KeyboardAmarok class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(KeyboardAmarok())
