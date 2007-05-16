    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoRegistrar.py
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoDeviceStrings import *

############################
# Visualization Class definition
##########################

class DeviceType:
	"""
	Types of visualizations
	"""
	
	Keyboard = 		"Keyboard"
	Mouse = 		"Mouse"
	Powermate = 		"Powermate"
	ATIX10 = 		"ATIX10"
	LIRC = 			"LIRC"
	Standard = 		"Standard"

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
		
		if self.DeviceType == DeviceType.Keyboard:
			Gizmod.printNiceScriptInit(0, "Keyboard", self.Device.DeviceName, self.Device.FileName)
			Gizmod.Keyboards.append(self.Device)
		elif self.DeviceType == DeviceType.Mouse:
			Gizmod.printNiceScriptInit(0, "Mouse", self.Device.DeviceName, self.Device.FileName)
			Gizmod.Mice.append(self.Device)
		elif self.DeviceType == DeviceType.Powermate:
			Gizmod.printNiceScriptInit(0, "Powermate", self.Device.DeviceName, self.Device.FileName)
			Gizmod.Powermates.append(self.Device)
		elif self.DeviceType == DeviceType.ATIX10:
			Gizmod.printNiceScriptInit(0, "ATI X10", self.Device.DeviceName, self.Device.FileName)
			Gizmod.ATIX10Remotes.append(self.Device)
			# set exlusive mode
			self.Device.grabExclusiveAccess(True)
		elif self.DeviceType == DeviceType.LIRC:
			Gizmod.printNiceScriptInit(0, "LIRC", self.Device.DeviceName, self.Device.FileName)
		else:
			Gizmod.printNiceScriptInit(0, "Standard", self.Device.DeviceName, self.Device.FileName)

	def handleDeviceRemoval(self):
		"""
		Remove the appropriate device from our internal list of devices
		"""

		if self.DeviceType == DeviceType.Keyboard:
			for item in Gizmod.Keyboards:
				if item.FileName == self.Device.FileName:
					Gizmod.Keyboards.remove(item)
					print "Removed Keyboard Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		elif self.DeviceType == DeviceType.Mouse:
			for item in Gizmod.Mice:
				if item.FileName == self.Device.FileName:
					Gizmod.Mice.remove(item)
					print "Removed Mouse Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		elif self.DeviceType == DeviceType.Powermate:
			for item in Gizmod.Powermates:
				if item.FileName == self.Device.FileName:
					Gizmod.Powermates.remove(item)
					print "Removed Powermate Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		elif self.DeviceType == DeviceType.ATIX10:
			# unset exlusive mode
			self.Device.grabExclusiveAccess(False)
			for item in Gizmod.ATIX10Remotes:
				if item.FileName == self.Device.FileName:
					Gizmod.ATIX10Remotes.remove(item)
					print "Removed ATI X10 Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
		elif self.DeviceType == DeviceType.LIRC:
			print "Removed LIRC Device: " + self.Device.DeviceName + " [" + self.Device.FileName + "]"
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
		self.DeviceType = "Unknown"
		self.__setDeviceType()
		
	def __setDeviceType(self):
		"""
		Set the device type
		"""

		if [i for i in KEYBOARD_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			self.DeviceType = DeviceType.Keyboard
		elif [i for i in MOUSE_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			self.DeviceType = DeviceType.Mouse
		elif [i for i in POWERMATE_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			self.DeviceType = DeviceType.Powermate
		elif [i for i in ATIX10_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			self.DeviceType = DeviceType.ATIX10
		elif [i for i in LIRC_GIZMOS if self.Device.DeviceName.lower().find(i) > -1]:
			self.DeviceType = DeviceType.LIRC
		else:
			self.DeviceType = DeviceType.Standard
			
############################
# GizmoRegistrar class end
##########################

for Mixer in DEFAULT_MIXERS:
	Gizmod.registerDefaultMixerPriority(Mixer)
