    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
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
INTERESTED_CLASSES = [GizmoEventClass.ATIX10]
INTERESTED_WINDOWS = ["mythfrontend"]

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
		
		# if the event is not a key release and the class is in INTERESTED_CLASSES 
		# and there is a ATIX10 and mouse attached then process the event
		if Event.Class in INTERESTED_CLASSES \
		   and [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1] \
		   and Event.Value != 0 and len(Gizmod.Keyboards) and len(Gizmod.Mice):
			# process the key
		   	if Event.Code == GizmoKey.KEY_WWW:
	   			subprocess.Popen(["firefox", "http://gizmod.sf.net"])
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
	Gizmod.Dispatcher.userScripts.append(ATIX10MythTV())
