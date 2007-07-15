    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Remote Control config
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
from GizmoRegistrar import *
from GizmoScriptEnableChecker import *
import sys

ENABLED = True
VERSION_NEEDED = 3.2

############################
# RemoteControl Class definition
##########################

class RemoteControl(GizmoScriptEnableChecker):
	"""
	Remote Control Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
	
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if it's not a remote event we're not interested!
		try:
			if not Event.Remote or not Gizmo:
				return False
		except AttributeError, msg:
			# this is fine
			return False
			
		Registrar = GizmoRegistrar(Gizmo)
		if Registrar.DeviceType == DeviceType.Keyboard and len(Gizmod.Keyboards):
			Gizmod.Keyboards[0].createEventRaw(Event.Type, Event.Code, Event.Value)
		elif Registrar.DeviceType == DeviceType.Mouse and len(Gizmod.Mice):
			if Event.Type == GizmoEventType.EV_ABS:
				EventType = GizmoEventType.EV_REL
				if Event.Code == 0x0:
					if self.LastX != -1:
						Gizmod.Mice[0].createEventRaw(GizmoEventType.EV_REL, Event.Code, Event.Value - self.LastX)
					self.LastX = Event.Value
				if Event.Code == 0x1:
					if self.LastY != -1:
						Gizmod.Mice[0].createEventRaw(GizmoEventType.EV_REL, Event.Code, Event.Value - self.LastY)
					self.LastY = Event.Value
			else:
				Gizmod.Mice[0].createEventRaw(Event.Type, Event.Code, Event.Value)
				
		# return False always so that events continue to get processed by other scripts
		return False
			
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptEnableChecker.__init__(self, ENABLED, VERSION_NEEDED)
		self.LastX = -1
		self.LastY = -1

############################
# RemoteControl class end
##########################

# register the user script
RemoteControl()
