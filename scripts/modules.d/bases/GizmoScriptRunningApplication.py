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

"""

  Copyright (c) 2007, Gizmo Daemon Team
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
"""

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
		if not GizmoScriptDefault.checkEvent(self, Event, Gizmo):
			return False

		# make sure the event is interesting to us
		if Gizmod.isProcessRunning(self.InterestedApplication) >= 0:
			# process the key
			return self.onDeviceEvent(Event, Gizmo)
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
