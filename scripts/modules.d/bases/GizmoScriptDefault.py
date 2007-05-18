    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoScript Default config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
import subprocess

############################
# GizmoScriptDefault Class definition
##########################

class GizmoScriptDefault:
	"""
	Event Mapping Base Class for the Default Mappings

	Inherit from this class if you want a default device event mapping
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
		if Event.Class in self.InterestedClasses and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
			self.onDeviceEvent(Event, Gizmo)
	   	else:
	   		# unmatched event, keep processing
			return False				
	
	############################
	# Private Functions
	##########################

	def __init__(self, Enabled, VersionNeeded, InterestedClasses):
		""" 
		Default Constructor
		"""
		
		self.Enabled = Enabled
		self.VersionNeeded = VersionNeeded
		self.InterestedClasses = InterestedClasses
		
		if self.Enabled:
			if not Gizmod.checkVersion(self.VersionNeeded, False):
				Gizmod.printNiceScriptInit(1, " * " + self.__class__.__name__, "NOT LOADED", "Version Needed: " + str(self.VersionNeeded))
			else:
				Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")
				Gizmod.Dispatcher.userScripts.append(self)
		else:
			Gizmod.printNiceScriptInit(1, " * " + self.__class__.__name__, "NOT LOADED", "Disabled")

############################
# GizmoScriptDefault class end
##########################
