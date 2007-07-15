    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Momo Racing config
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
from GizmoScriptActiveApplication import *

ENABLED = True
VERSION_NEEDED = 3.3
INTERESTED_CLASSES = [GizmoEventClass.Standard]
INTERESTED_PRODUCTS = [51715]
INTERESTED_VENDORS = [1133]

############################
# MomoRacing Class definition
##########################

class MomoRacing(GizmoScriptDefault):
	"""
	Logitech Momo Racing Event Mapping
	"""
	
	############################
	# Public Functions
	##########################
			
	def onDeviceEvent(self, Event, Gizmo = None):
		"""
		Called from Base Class' onEvent method.
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
	   	# Only interact with Racing if it's the first Momo
	  	if Gizmo.DeviceIDVendor in INTERESTED_VENDORS and Gizmo.DeviceIDProduct in INTERESTED_PRODUCTS:
		   	# Check for pedals
			if Event.Type == GizmoEventType.EV_ABS and Event.Code == 0x01:
				self.scrollSpeed = 0x7f - Event.Value
				self.setScrolling()
				return True
		return False
	
	def setScrolling(self):
		""" Start / Stop scrolling """
		
		# cancel scrolling
		if self.scrollSpeed == 0:
			if self.scrollTimer:
				self.scrollTimer.cancel()
				self.scrollTimer = None
			return
			
		# start scrolling
		Percent = abs(self.scrollSpeed) / 128.0
		print Percent
		#if Percent > 0.75:
		#	self.scrollTimeout = 2.0 / abs(self.scrollSpeed)
		#else:
		#	self.scrollTimeout = 10.0 / abs(self.scrollSpeed)
		ss = abs(self.scrollSpeed)
		self.scrollTimeout = 250.0 / (ss * ss)
		if self.scrollSpeed < 0:
			self.scrollValue = -1
		else:
			self.scrollValue = 1
		
		if not self.scrollTimer:
			self.scrollTimer = GizmodTimer(self.scrollTimeout, self.__timerCallback, -1, None)
			self.scrollTimer.start()
		else:
			self.scrollTimer.setTime(self.scrollTimeout)

	############################
	# Private Functions
	##########################
	
	def __doScroll(self):
		""" scroll via the mouse """
		Gizmod.Mice[0].createEventRaw(GizmoEventType.EV_REL, GizmoMouseAxis.WHEEL, -self.scrollValue)

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		GizmoScriptDefault.__init__(self, ENABLED, VERSION_NEEDED, INTERESTED_CLASSES)
		self.scrollSpeed = 0
		self.scrollTimer = None
				
	def __timerCallback(self, UserData):
		""" Callback function for the timer """

		if self.scrollSpeed == 0:
			return
			
		# scroll slowly (create a mouse wheel event)
		self.__doScroll()
		self.setScrolling()

############################
# MomoRacing class end
##########################

# register the user script
MomoRacing()
