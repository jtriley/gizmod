    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	ATIX10 MPlayer config
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
INTERESTED_WINDOWS = ["mplayer"]

############################
# ATIX10MPlayer Class definition
##########################

class ATIX10MPlayer:
	"""
	MPlayer ATIX10 Event Mapping
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
		if Event.Class in INTERESTED_CLASSES \
		   and [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1] \
		   and Event.Value != 0 and len(Gizmod.Keyboards) and len(Gizmod.Mice):
			# process the key
		   	if Event.Code == GizmoKey.KEY_POWER:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PAUSE:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PLAY:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_STOP:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SPACE)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_BOOKMARKS:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_V)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_EDIT:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_O)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_REWIND:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_FORWARD:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEUP)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_COFFEE:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_Q)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_C:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_MINUS)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_D:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_EQUAL)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
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
# ATIX10MPlayer class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(ATIX10MPlayer())
