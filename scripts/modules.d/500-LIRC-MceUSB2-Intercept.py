    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	LIRCMceUSB2 Intercept config
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
from GizmoScriptAltTabber import *
import subprocess

ENABLED = True
VERSION_NEEDED = 3.3
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
USES_LIRC_REMOTES = ["mceusb", "mceusb2"]

############################
# LIRCMceUSB2Intercept Class definition
##########################

class LIRCMceUSB2Intercept(GizmoScriptDefault):
	"""
	Intercept LIRC Event Mapping for the MceUSB2 remote
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function.
		"""

		# if the event isn't from the remote we're interested in don't handle it
		if Event.Remote not in USES_LIRC_REMOTES:
			return False

		# process the key
	   	if Event.Button == "Home" and self.AltTabber.isAltTabbing():
	   		self.AltTabber.doAltTab()
	   		return True
	   	else:
	   		# unmatched event, keep processing
			return False				
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptDefault.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES)
		self.AltTabber = GizmoScriptAltTabber()

############################
# LIRCMceUSB2Intercept class end
##########################

# register the user script
LIRCMceUSB2Intercept()
