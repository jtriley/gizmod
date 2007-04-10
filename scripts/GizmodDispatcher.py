    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	GizmodDispatcher.py
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from   GizmoDaemon import *

############################
# GizmodDispatcher Class definition
##########################

class GizmodDispatcher(GizmodEventHandler):
	"""
	Main class that handles all of the incoming events
	"""
	
	############################
	# Public Functions
	##########################

	def getInitialized(self):
		""" Gets whether or not the object has been initialized """
		
		return self.initialized

	def initialize(self):
		"""
		This python function gets called by GizmoDeamon and is intended to allow for
		user specific initialization code to be executed during program startup.
		"""

		print "GizmoDaemon Config Script v" + Gizmod.getVersion()  + " -- Initializing"
		self.initialized = True
		
	def onEvent(self, Event):
		"""
		This method gets called whenever Gizmo Daemon detects an event from a device
		 
		The Event object passed in will be of the type associated with that event,
		so for example if it's a powermate event the Event class will be "Powermate"
		
		All event classes share the same base "Event" class, and you can use the Event
		class method "getEventType" (amongst others) to figure out what type of event it 
		is.
		
		See the C++ API documention on the specific GizmoEvent* type for more details
		"""
		
		print "onEvent: " + Event.getEventType()
		
	def onQueryDeviceType(self, DeviceName, DeviceIDBusType, DeviceIDVendor, DeviceIDProduct, DeviceIDVersion, FileName):
		"""
		This method is triggered when a new device is being registered (either at startup
		or when Gizmo Daemon detects a new device has been plugged in to the computer)
		
		This method should return the GizmoClass of the device
		"""
		
		return GizmoDeviceType(DeviceName, DeviceIDBusType, DeviceIDVendor, DeviceIDProduct, DeviceIDVersion, FileName).DeviceType

	############################
	# Private Functions
	##########################

	def __construct__(self):
		""" 
		Default Constructor -- Use this rather than __init__
		"""

		self.initialized = False

############################
# GizmodDispatcher class end
##########################

# To run user defined code post initializing, see User.py which is executed 
# after this file is parsed, and:
#
# - An interface to the main C++ program core is availabe via the 
#   object "Gizmod"
# - An instantiation of the GizmodDispatcher is available as "Dispatcher"
