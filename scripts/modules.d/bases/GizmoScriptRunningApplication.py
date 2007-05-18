    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoScript RunningApplication config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoScriptDefault import *
import subprocess

############################
# GizmoScriptRunningApplication Class definition
##########################

class GizmoScriptRunningApplication(GizmoScriptDefault):
	"""
	Event Mapping Base Class for Running Application Mappings
	
	Inherit from this class if you want to define a per application event mapping
	where the application just has to be running (but not necessarily currently focused)
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# check with the base class to see if we're interested in the event
		if not GizmoScriptDefault.onEvent(self, Event, Gizmo):
			return False

		# make sure the event is interesting to us
		if Gizmod.isProcessRunning(self.InterestedApplication) >= 0:
			# process the key
			self.onDeviceEvent(Event, Gizmo)
	   	else:
	   		# unmatched event, keep processing
			return False				
	
	############################
	# Private Functions
	##########################

	def __init__(self, Enabled, VersionNeeded, InterestedClasses, InterestedApplication):
		""" 
		Default Constructor
		"""
		
		# call base constructor
		GizmoScriptDefault.__init__(self, Enabled, VersionNeeded, InterestedClasses)
		
		# initialize
		self.InterestedApplication = InterestedApplication

############################
# GizmoScriptRunningApplication class end
##########################
