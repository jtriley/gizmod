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
		if not GizmoScriptDefault.checkEvent(self, Event, Gizmo):
			return False

		# make sure the event is interesting to us
		if [i for i in self.InterestedWindows if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1]:
			# process the key
			return self.onDeviceEvent(Event, Gizmo)
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
