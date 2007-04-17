    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	GizmoRegistrar.py
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

############################
# GizmoRegistrar Class definition
##########################

class GizmoRegistrar:
	"""
	This class is responsible for any book keeping that needs to occur
	after a new device has been registered with the system, and when a 
	device is being disconnected.
	
	This is where individual devices are chosen based on their device name,
	product code, vendor ID, etc.
	
	So for example, a device with "Keyboard" in the name is registered
	as a Keyboard with Gizmo Daemon.
	"""
	
	############################
	# Public Functions
	##########################
	
	def handleDeviceAddition(self):
		"""
		Add the appropriate device to our internal list of devices
		base on the actual type of the device.
		"""

		print "Register: " + self.Device.DeviceName

	def handleDeviceRemoval(self):
		"""
		Remove the appropriate device from our internal list of devices
		"""

		print "Remove: " + self.Device.DeviceName
		
	############################
	# Private Functions
	##########################

	def __init__(self, Device):
		""" 
		Default Constructor
		"""
		
		self.Device = Device

############################
# GizmoRegistrar class end
##########################
