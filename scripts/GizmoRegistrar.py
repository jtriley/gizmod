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

# list of devices to enumerate as keyboards
KEYBOARD_GIZMOS = ["keyboard"]

# list of devices to enumerate as mice
MOUSE_GIZMOS = ["mouse", "trackball", "touchpad"]

# list of devices to enumerate as mice
POWERMATE_GIZMOS = ["powermate", "soundknob"]

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

		if [i for i in KEYBOARD_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			print "Registered Keyboard Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
			Gizmod.Keyboards.append(self.Device)
		elif [i for i in MOUSE_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			print "Registered Mouse Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
			Gizmod.Mice.append(self.Device)
		elif [i for i in POWERMATE_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			print "Registered Powermate Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
			Gizmod.Powermates.append(self.Device)
		else:
			print "Registered Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"

	def handleDeviceRemoval(self):
		"""
		Remove the appropriate device from our internal list of devices
		"""

		if [i for i in KEYBOARD_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			for item in Gizmod.Keyboards:
				if item.FileName == self.Device.FileName:
					Gizmod.Keyboards.remove(item)
					print "Removed Keyboard Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		elif [i for i in MOUSE_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			for item in Gizmod.Mice:
				if item.FileName == self.Device.FileName:
					Gizmod.Mice.remove(item)
					print "Removed Mouse Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		elif [i for i in POWERMATE_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			for item in Gizmod.Powermates:
				if item.FileName == self.Device.FileName:
					Gizmod.Powermates.remove(item)
					print "Removed Powermate Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		else:
			print "Removed Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
			
		
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
