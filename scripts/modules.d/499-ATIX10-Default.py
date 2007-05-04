    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	ATIX10 Default config
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
INTERESTED_CLASSES = [GizmoEventClass.ATIX10]

############################
# ATIX10Default Class definition
##########################

class ATIX10Default:
	"""
	Default ATIX10 Event Mapping
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
		if Event.Class in INTERESTED_CLASSES and len(Gizmod.Keyboards) and len(Gizmod.Mice):
			# process the key
			if Event.Code == GizmoKey.BTN_LEFT:
				# do mouse left click
				Gizmod.Mice[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_BTN_LFT, Event.Value)
				return True
			elif Event.Code == GizmoKey.BTN_RIGHT:
				# do mouse right click
				Gizmod.Mice[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_BTN_RIGHT, Event.Value)
				return True
			elif Event.Type == GizmoEventType.EV_REL:
				# do mouse movements
				Gizmod.Mice[0].createEvent(GizmoEventType.EV_REL, Event.Code, Event.Value)
				return True
			elif Event.Value != 0:
				# do button presses
			   	if Event.Code == GizmoKey.KEY_WWW:
		   			subprocess.Popen(["firefox", "http://gizmod.sf.net"])
			   		return True
			   	elif Event.Code == GizmoKey.KEY_VOLUMEUP:
		   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback + 1
			   		return True
			   	elif Event.Code == GizmoKey.KEY_VOLUMEDOWN:
		   			Gizmod.DefaultMixerVolume.VolumePlayback = Gizmod.DefaultMixerVolume.VolumePlayback - 1
			   		return True
			   	elif Event.Code == GizmoKey.KEY_MUTE:
		   			Gizmod.toggleMuteAllCards()
			   		return True
			   	elif Event.Code == GizmoKey.KEY_OK:
					Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
			   		return True
			   	else:
			   		# directly translate all other events
					Gizmod.Keyboards[0].createEvent(Event.Type, Event.Code, Event.Value)
					return True
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
# ATIX10Default class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(ATIX10Default())
