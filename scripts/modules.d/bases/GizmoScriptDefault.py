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
from GizmoScriptEnableChecker import *
import subprocess

############################
# GizmoScriptDefault Class definition
##########################

class GizmoScriptDefault(GizmoScriptEnableChecker):
	"""
	Event Mapping Base Class for the Default Mappings

	Inherit from this class if you want a default device event mapping
	"""
	
	############################
	# Public Functions
	##########################
	
	def checkEvent(self, Event, Gizmo = None):
		"""
		Test if an event should go through or not
		"""
			
		# if the event class is in INTERESTED_CLASSES and the active window is
		# one of INTERESTED_WINDOWS and there is a keyboard and mouse attached 
		# then process the event
		if Event.Class in self.InterestedClasses and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
			return True
	   	else:
	   		# unmatched event, keep processing
			return False
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		if self.checkEvent(Event, Gizmo):
			return self.onDeviceEvent(Event, Gizmo)
		else:
			return False
		
	############################
	# Private Functions
	##########################

	def __init__(self, Enabled, VersionNeeded, InterestedClasses):
		""" 
		Default Constructor
		"""
		
		self.InterestedClasses = InterestedClasses
		GizmoScriptEnableChecker.__init__(self, Enabled, VersionNeeded)		

############################
# GizmoScriptDefault class end
##########################
