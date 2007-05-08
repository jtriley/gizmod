    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	ATIX10 MythTV config
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
INTERESTED_WINDOWS = ["mythfrontend"]
POWER_APPLICATION = "mythfrontend"

############################
# ATIX10MythTV Class definition
##########################

class ATIX10MythTV:
	"""
	MythTV ATIX10 Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# check for power button
		# if pressed and mythfrontend isn't running, then launch it
		# also return False so that other scripts may make use of the power
		# button as well
		if Event.Class in INTERESTED_CLASSES \
		   and Event.Code == GizmoKey.KEY_POWER \
		   and Gizmod.isProcessRunning(POWER_APPLICATION) < 0:
   			subprocess.Popen([POWER_APPLICATION])
   			Gizmod.updateProcessTree() # force an instantaneous process tree update
	   		return False

		# if the event is not a key release and the class is in INTERESTED_CLASSES 
		# and there is a ATIX10 and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES \
		   and [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1] \
		   and Event.Value != 0 and len(Gizmod.Keyboards) and len(Gizmod.Mice):
			# process the key
		   	if Event.Code == GizmoKey.KEY_POWER:
		   		# if mythfrontend is open, kill it
	   			subprocess.Popen(["killall", "mythfrontend"])
		   		return True
		   	elif Event.Code == GizmoKey.KEY_A:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_A)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_B:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_B)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PROG1:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PROG2:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_SLASH)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_WWW:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_V)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_BOOKMARKS:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_N)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_EDIT:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_I)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_VOLUMEUP:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTBRACE)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_VOLUMEDOWN:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTBRACE)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_CHANNELUP:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_CHANNELDOWN:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_MENU:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_M)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_KPENTER:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_END)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_C:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_C)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_D:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_D)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_COFFEE:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_FRONT:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_HOME)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_E:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_H)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_F:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_M)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_REWIND:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_COMMA)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PLAYCD:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_FORWARD:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_DOT)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHTSHIFT, 0)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_RECORD:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_R)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_STOP:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_S)
		   		return True
		   	elif Event.Code == GizmoKey.KEY_PAUSE:
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
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
# ATIX10MythTV class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * ATIX10MythTV", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(ATIX10MythTV())
