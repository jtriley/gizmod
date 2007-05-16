    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Remote Control config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoRegistrar import *
import sys

ENABLED = True
VERSION_NEEDED = 3.1

############################
# RemoteControl Class definition
##########################

class RemoteControl:
	"""
	Remote Control Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
	
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if it's not a remote event we're not interested!
		if not Event.Remote or not Gizmo:
			return False
			
		Registrar = GizmoRegistrar(Gizmo)
		if Registrar.DeviceType == DeviceType.Keyboard and len(Gizmod.Keyboards):
			Gizmod.Keyboards[0].createEvent(Event.Type, Event.Code, Event.Value)
		elif Registrar.DeviceType == DeviceType.Mouse and len(Gizmod.Mice):
			if Event.Type == GizmoEventType.EV_ABS:
				EventType = GizmoEventType.EV_REL
				if Event.Code == 0x0:
					if self.LastX != -1:
						Gizmod.Mice[0].createEvent(GizmoEventType.EV_REL, Event.Code, Event.Value - self.LastX)
					self.LastX = Event.Value
				if Event.Code == 0x1:
					if self.LastY != -1:
						Gizmod.Mice[0].createEvent(GizmoEventType.EV_REL, Event.Code, Event.Value - self.LastY)
					self.LastY = Event.Value
			else:
				Gizmod.Mice[0].createEvent(Event.Type, Event.Code, Event.Value)
				
		# return False always so that events continue to get processed by other scripts
		return False
			
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")
		self.LastX = -1
		self.LastY = -1

############################
# RemoteControl class end
##########################

# register the user script
if ENABLED and Gizmod.UseRemoteControl:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * RemoteControl", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(RemoteControl())
