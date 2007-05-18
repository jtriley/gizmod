    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoScript ActiveApplication config
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
# GizmoScriptActiveApplication Class definition
##########################

class GizmoScriptActiveApplication(GizmoScriptDefault):
	"""
	Event Mapping Base Class for the ActiveApplication Mappings
	
	Inherit from this class if you want to define a per application event mapping
	where the application has to be the currently focused app
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
		if [i for i in self.InterestedWindows if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1]:
			# process the key
			self.onDeviceEvent(Event, Gizmo)
	   	else:
	   		# unmatched event, keep processing
			return False				
	
	############################
	# Private Functions
	##########################

	def __init__(self, Enabled, VersionNeeded, InterestedClasses, InterestedWindows):
		""" 
		Default Constructor
		"""
		
		# call base constructor
		GizmoScriptDefault.__init__(self, Enabled, VersionNeeded, InterestedClasses)
		
		# initialize
		self.InterestedWindows = InterestedWindows

############################
# GizmoScriptActiveApplication class end
##########################
