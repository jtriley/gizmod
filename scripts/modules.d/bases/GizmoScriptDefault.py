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
