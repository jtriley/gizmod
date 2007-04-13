    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	GizmoDeviceType.py
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

############################
# GizmoDeviceType Class definition
##########################

class GizmoDeviceType:
	"""
	This class is responsible for telling GizmoDaemon what the class
	of the devices are that are attached to the system.  Ie, if 
	Gizmo Daemon deteces "KeyTronic Keyboard" this class should respond
	by setting its type to Gizmod.GizmoClass.Standard -- See the C++ API
	documention regarding Gizmo.hpp for a complete list (and description)
	of the available enums.
	
	This is provided as a way of manually intervening in the device
	registration process.  There are cases where certain devices enumerate
	themselves with unintuitive descriptions such as "
	"""
	
	############################
	# Public Functions
	##########################
	
	def setDeviceType(self, DeviceInfo):
		"""
		Calculate the device type from the device ID info

		For information regarding the DeviceInformation fields see the API documention for
		H::DeviceInfo, but the following fields are available:
			- DeviceIDBusType;	< Bus Type of the device
			- DeviceIDProduct;	< Product code of the device
			- DeviceIDVendor;	< Vendor ID of the device
			- DeviceIDVersion;	< Version of the device
			- DeviceName;		< Name of the device
			- FileName	 	< Name of the file to watch
		"""
		
		#print "onQueryDeviceType: " + self.DeviceName + " [" + self.FileName + "]"
		if DeviceInfo.DeviceName.lower().find("powermate") > -1 or \
 		   DeviceInfo.DeviceName.lower().find("soundknob") > -1:
 			self.DeviceType = GizmoClass.Powermate
 		elif DeviceInfo.DeviceName.lower().find("ati x10") > -1:
	 		self.DeviceType = GizmoClass.ATIX10
 		elif DeviceInfo.DeviceName.lower().find("lirc") > -1:
	 		self.DeviceType = GizmoClass.LIRC
 		elif DeviceInfo.DeviceName.lower().find("cpu") > -1:
	 		self.DeviceType = GizmoClass.CPU
	 	else:
	 		self.DeviceType = GizmoClass.Standard

	############################
	# Private Functions
	##########################

	def __init__(self, DeviceInformation):
		""" 
		Default Constructor
		"""
		
		self.DeviceInfo = DeviceInformation
		self.DeviceType = GizmoClass.Standard
		
		# set the device type from above info
		self.setDeviceType(self.DeviceInfo)

############################
# GizmoDeviceType class end
##########################
