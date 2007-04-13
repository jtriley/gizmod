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

from GizmoDaemon import *
from GizmoDeviceType import GizmoDeviceType

############################
# GizmodDispatcher Class definition
##########################

class GizmodDispatcher(GizmodEventHandler):
	"""
	Main class that handles all of the incoming events
	
	The idea behind this class is to use it as nothing more than a dispatching
	mechanism.  All the events get channeled from GizmoDaemon through here
	and this class is intended merely to pass events off the appropriate
	module.
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
		
	def onEvent(self, Event, Gizmo):
		"""
		This method gets called whenever Gizmo Daemon detects an event from a device
		 
		The Event object passed in will be of the type associated with that event,
		so for example if it's a Powermate event the Event class will be "Powermate"
		
		Similarly the Gizmo object will of the class of the device that generated
		the event. Ie, if it's a Powermate event the class will also be "Powermate"
		
		All Event classes share the same base "Event" class, and you can use the Event
		class method "getEventType" (amongst others) to figure out what type of event it 
		is.  See the C++ API documention on the specific GizmoEvent* type for more details

		All Gizmo classes share the same base "Gizmo" class, and you can use the Gizmo
		class method "getGizmoType" (amongst others) to figure out what type of event it 
		is.  See the C++ API documention on the specific Gizmo* type for more details
		"""
		
		if Event.EventType != "Powermate":
			print "onEvent: " + Event.EventType + " -- " + Gizmo.FileName + " | c: " + str(hex(Event.RawCode)) +  " t: " + str(hex(Event.RawType)) +  " v: " + str(hex(Event.RawValue))  
		
	def onQueryDeviceType(self, DeviceInformation):
		"""
		This method is triggered when a new device is being registered (either at startup
		or when Gizmo Daemon detects a new device has been plugged in to the computer)
		
		For information regarding the DeviceInformation fields see the API documention for
		H::DeviceInfo
		
		This method should return the GizmoClass of the device
		"""
		
		# GizmoDeviceType is defined in GizmoDeviceType.py for convenience and modularity sake
		return GizmoDeviceType(DeviceInformation).DeviceType

	############################
	# Private Functions
	##########################
	
	def __init__(self):
		""" 
		Default Constructor
		"""

		# Must explicitely call the base's constructor
		GizmodEventHandler.__init__(self)
		
		# Module specific initialization
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
