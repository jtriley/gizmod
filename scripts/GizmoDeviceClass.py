    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	GizmoDeviceClass.py
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

# list of devices to enumerate as mice
POWERMATE_GIZMOS = ["powermate", "soundknob"]

############################
# GizmoDeviceClass Class definition
##########################

class GizmoDeviceClass:
	"""
	This class is responsible for telling GizmoDaemon what the class
	of the devices are that are attached to the system.  Ie, if 
	Gizmo Daemon detects "KeyTronic Keyboard" this class should respond
	by setting its type to Gizmod.GizmoClass.Standard -- See the C++ API
	documention regarding Gizmo.hpp for a complete list (and description)
	of the available enums.
	
	This is provided as a way of manually intervening in the device
	registration process.  There are cases where certain devices enumerate
	themselves with unintuitive descriptions such as "InniTech 
	Corp Device v.413" or <blank>.

	There are a number of device identification fields available
	include product and vendor codes.
	"""
	
	############################
	# Public Functions
	##########################
	
	def setDeviceClass(self, DeviceInfo):
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
		
		#print "onQueryDeviceType: " + DeviceInfo.DeviceName + " [" + DeviceInfo.FileName + "] Prod: " + str(hex(DeviceInfo.DeviceIDProduct))
		if [i for i in POWERMATE_GIZMOS if DeviceInfo.DeviceName.lower().find(i) > -1]:
 			self.DeviceClass = GizmoClass.Powermate
 		elif DeviceInfo.DeviceName.lower().find("ati x10") > -1:
	 		self.DeviceClass = GizmoClass.ATIX10
 		elif DeviceInfo.DeviceName.lower().find("lirc") > -1:
	 		self.DeviceClass = GizmoClass.LIRC
		elif DeviceInfo.DeviceName.lower().find("cpu") > -1:
	 		self.DeviceClass = GizmoClass.CPU
	 	else:
	 		self.DeviceClass = GizmoClass.Standard

	############################
	# Private Functions
	##########################

	def __init__(self, DeviceInformation):
		""" 
		Default Constructor
		"""
		
		self.DeviceInfo = DeviceInformation
		self.DeviceClass = GizmoClass.Standard
		
		# set the device type from above info
		self.setDeviceClass(self.DeviceInfo)

############################
# GizmoDeviceClass class end
##########################
