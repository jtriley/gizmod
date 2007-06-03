    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoScript EnableChecker config
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
import subprocess

############################
# GizmoScriptEnableChecker Class definition
##########################

class GizmoScriptEnableChecker:
	"""
	Base Class that checks whether or not a script should be enabled
	"""
	
	############################
	# Public Functions
	##########################
	
	############################
	# Private Functions
	##########################

	def __init__(self, Enabled, VersionNeeded):
		""" 
		EnableChecker Constructor
		"""
		
		self.Enabled = Enabled
		self.VersionNeeded = VersionNeeded
		
		if self.Enabled:
			if not Gizmod.checkVersion(self.VersionNeeded, False):
				Gizmod.printNiceScriptInit(1, " * " + self.__class__.__name__, "NOT LOADED", "Version Needed: " + str(self.VersionNeeded))
			else:
				Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")
				Gizmod.Dispatcher.userScripts.append(self)
		else:
			Gizmod.printNiceScriptInit(1, " * " + self.__class__.__name__, "NOT LOADED", "Disabled")

############################
# GizmoScriptEnableChecker class end
##########################
