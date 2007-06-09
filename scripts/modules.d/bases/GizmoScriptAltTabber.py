    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoScript AltTabber config
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
from GizmoDeviceStrings import *
import subprocess

############################
# GizmoScriptAltTabber Class definition
##########################

class GizmoScriptAltTabber:
	"""
	Inherit from this class if you want to send Alt-Tab events
	"""
	
	############################
	# Public Functions
	##########################
	
	def doAltTab(self):
		"""
		Figure out what combination of keys to press to do the next iteration of the Alt-Tab events
		"""
				
		if not self.AltTabbing:
			Gizmod.Keyboards[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 1)
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_TAB)
			self.TimeoutTimer = GizmodTimer(ALT_TAB_TIMEOUT, self.timerCallback, None)
			self.TimeoutTimer.start()
			self.AltTabbing = True
		else:
			Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_TAB)
			self.TimeoutTimer.resetTimer()
			
	def timerCallback(self, UserData):
		"""
		Callback function for the timer
		"""
		
		if not self.AltTabbing:
			return
			
		Gizmod.Keyboards[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 0)
		self.AltTabbing = False
		
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		self.AltTabbing = False
		self.TimeoutTimer = None

############################
# GizmoScriptDefault class end
##########################
