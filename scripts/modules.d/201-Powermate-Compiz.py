    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate Compiz config
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
import time

ENABLED = True
VERSION_NEEDED = 3.3
INTERESTED_CLASSES = [GizmoEventClass.Powermate]

############################
# PowermateCompiz Class definition
##########################

class PowermateCompiz(GizmoScriptDefault):
	"""
	Compiz Powermate Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
					
		if self.Unfolded and Event.Type == GizmoEventType.EV_REL:
			if Event.Value < 0:
				for repeat in range(abs(Event.Value)):
					Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
			else:
				for repeat in range(abs(Event.Value)):
					Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
			return True
			
		return False
		
	def onDeviceEventButtonTimeout(self, Gizmo):
		"""
		Called when a Powermate's button times out
		
		This is generated from 200-Powermate-ButtonTimeout.py
		"""
		
		#print "Button Timeout in [" + self.__class__.__name__ + "] from [" + str(Gizmo.Type) + " " + str(Gizmo.DeviceClassID) + "]"
		Gizmod.Keyboards[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 1)
		Gizmod.Keyboards[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 1)
		Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_PAGEDOWN)
		self.Unfolded = True
		
		return True
		
	def onDeviceEventEaten(self, Event, Gizmo):
		"""
		Called when a Powermate's button is released after timing out
		
		This is generated from 200-Powermate-ButtonTimeout.py
		"""
		
		#print "Device Event Eaten in [" + self.__class__.__name__ + "] from [" + str(Gizmo.Type) + " " + str(Gizmo.DeviceClassID) + "]"
		if self.Unfolded and Event.Type == GizmoEventType.EV_KEY and Event.Value == 0:
			Gizmod.Keyboards[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTCTRL, 0)
			Gizmod.Keyboards[0].createEventRaw(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTALT, 0)
			self.Unfolded = False
			return True
			
		return False
		
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptDefault.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES)
		self.Unfolded = False

############################
# PowermateCompiz class end
##########################

# register the user script
PowermateCompiz()
