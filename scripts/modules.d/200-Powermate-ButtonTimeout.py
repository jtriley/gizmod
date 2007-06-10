    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate ButtonTimeout config
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
from GizmoDeviceStrings import *
import time

ENABLED = True
VERSION_NEEDED = 3.3
INTERESTED_CLASSES = [GizmoEventClass.Powermate]

############################
# PowermateButtonTimeout Class definition
##########################

class PowermateButtonTimeout(GizmoScriptDefault):
	"""
	ButtonTimeout Powermate Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
				
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""

	   	# Check for rotations
		if Event.Type == GizmoEventType.EV_KEY:
			if Event.Value == 1:
				#print "Powermate Button Timeout Timer Created [" + str(POWERMATE_BUTTON_TIMEOUT) + "s]"
				self.ButtonTimeoutTimers[Gizmo.FileName] = GizmodTimer(POWERMATE_BUTTON_TIMEOUT, self.timerCallback, Gizmo)
				self.ButtonTimeoutTimers[Gizmo.FileName].start()
				self.ButtonTimeoutEatNexts[Gizmo.FileName] = False
			else:
				if not self.ButtonTimeoutEatNexts[Gizmo.FileName]:
					#print "Powermate Button Timeout Timer Canceled"
					self.ButtonTimeoutTimers[Gizmo.FileName].cancel()
				else:
					#print "Powermate Button Event Eaten due to Button Timeout"
					self.ButtonTimeoutEatNexts[Gizmo.FileName] = False
					
					# loop through all the user scripts and fire off the event
					# if they handle it
					for UserScript in Gizmod.Dispatcher.userScripts:
						if UserScript.__class__.__name__.find("Powermate") == -1:
							continue
						if "onDeviceEventEaten" in dir(UserScript):
							if UserScript.onDeviceEventEaten(Event, Gizmo):
								break
					return True
		elif Event.Type == GizmoEventType.EV_REL:
			if self.ButtonTimeoutTimers[Gizmo.FileName]:
				self.ButtonTimeoutTimers[Gizmo.FileName].cancel()
		return False
		
	def onDeviceEventButtonTimeout(self, Gizmo):
		"""
		Called when a Powermate's button times out
		
		This is generated from 200-Powermate-ButtonTimeout.py
		"""
		
		#print "Button Timeout in [" + self.__class__.__name__ + "] from [" + str(Gizmo.Type) + " " + str(Gizmo.DeviceClassID) + "]"
		return False

	def onDeviceEventEaten(self, Event, Gizmo):
		"""
		Called when a Powermate's button is released after timing out
		
		This is generated from 200-Powermate-ButtonTimeout.py
		"""
		
		#print "Device Event Eaten in [" + self.__class__.__name__ + "] from [" + str(Gizmo.Type) + " " + str(Gizmo.DeviceClassID) + "]"
		return False
		
	def timerCallback(self, UserData):
		"""
		Timer function callback
		"""

		# set the eat next state		
		self.ButtonTimeoutEatNexts[UserData.FileName] = True
		
		# loop through all the user scripts and fire off the event
		# if they handle it
		for UserScript in Gizmod.Dispatcher.userScripts:
			if UserScript.__class__.__name__.find("Powermate") == -1:
				continue
			if "onDeviceEventButtonTimeout" in dir(UserScript):
				if UserScript.onDeviceEventButtonTimeout(UserData):
					break
		
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptDefault.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES)
		self.ButtonTimeoutTimers = {}
		self.ButtonTimeoutEatNexts = {}

############################
# PowermateButtonTimeout class end
##########################

# register the user script
PowermateButtonTimeout()
