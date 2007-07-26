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
			Gizmod.printNiceScriptRegister(0, "Keyboard", self.Device.DeviceName, self.Device.FileName, hex((self.Device.DeviceIDVendor)), hex((self.Device.DeviceIDProduct)))
			Gizmod.Keyboards.append(self.Device)
		elif self.DeviceType == DeviceType.Mouse:
			Gizmod.printNiceScriptRegister(0, "Mouse", self.Device.DeviceName, self.Device.FileName, hex((self.Device.DeviceIDVendor)), hex((self.Device.DeviceIDProduct)))
			Gizmod.Mice.append(self.Device)
		elif self.DeviceType == DeviceType.Powermate:
			Gizmod.printNiceScriptRegister(0, "Powermate", self.Device.DeviceName, self.Device.FileName, hex((self.Device.DeviceIDVendor)), hex((self.Device.DeviceIDProduct)))
			Gizmod.Powermates.append(self.Device)
			self.Device.setRotateSensitivity(POWERMATE_ROTATE_SENSITIVITY)
		elif self.DeviceType == DeviceType.ATIX10:
			Gizmod.printNiceScriptRegister(0, "ATI X10", self.Device.DeviceName, self.Device.FileName, hex((self.Device.DeviceIDVendor)), hex((self.Device.DeviceIDProduct)))
			Gizmod.ATIX10Remotes.append(self.Device)
			# set exlusive mode
			self.Device.grabExclusiveAccess(True)
		elif self.DeviceType == DeviceType.LIRC:
			Gizmod.printNiceScriptRegister(0, "LIRC", self.Device.DeviceName, self.Device.FileName, hex((self.Device.DeviceIDVendor)), hex((self.Device.DeviceIDProduct)))
		else:
			Gizmod.printNiceScriptRegister(0, "Standard", self.Device.DeviceName, self.Device.FileName, hex((self.Device.DeviceIDVendor)), hex((self.Device.DeviceIDProduct)))

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
		
	def __checkDeviceType(self, DeviceTypes):
		""" check a device type """
		
		for i in DeviceTypes:
			# see if the device descrption matches
			if self.Device.DeviceName.lower().find(i) > -1:
				if i[0] == "!":
					return False
				else:
					return True
			# see if they specified by device node
			elif self.Device.FileName.lower().find(i) > -1:
				return True
			else:
				# check for venfor / product IDs
				cPos =  i.find(":")
				if cPos > -1:
					Vendor = i[0 : cPos]
					Product = i[cPos + 1 : len(i)]
					if Vendor == str(hex(self.Device.DeviceIDVendor)) and Product == str(hex(self.Device.DeviceIDProduct)):
						return True
				
		return False
		
	def __setDeviceType(self):
		"""
		Set the device type
		"""
		
		if self.__checkDeviceType(KEYBOARD_GIZMOS):	
			self.DeviceType = DeviceType.Keyboard
		elif self.__checkDeviceType(MOUSE_GIZMOS):
			self.DeviceType = DeviceType.Mouse
		elif self.__checkDeviceType(POWERMATE_GIZMOS):
			self.DeviceType = DeviceType.Powermate
		elif self.__checkDeviceType(ATIX10_GIZMOS):
			self.DeviceType = DeviceType.ATIX10
		elif self.__checkDeviceType(LIRC_GIZMOS):
			self.DeviceType = DeviceType.LIRC
		else:
			self.DeviceType = DeviceType.Standard
			
############################
# GizmoRegistrar class end
##########################

for Mixer in DEFAULT_MIXERS:
	Gizmod.registerDefaultMixerPriority(Mixer)
