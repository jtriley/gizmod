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
	
	def setDeviceType(self):
		"""
		Calculate the device type from the device ID info
		"""
		print "onQueryDeviceType: " + self.DeviceName + " [" + self.FileName + "]"
		self.DeviceType = GizmoClass.Standard

	############################
	# Private Functions
	##########################

	def __init__(self, DeviceName, DeviceIDBusType, DeviceIDVendor, DeviceIDProduct, DeviceIDVersion, FileName):
		""" 
		Default Constructor
		"""
		self.DeviceName = DeviceName
		self.DeviceIDBusType = DeviceIDBusType
		self.DeviceIDVendor = DeviceIDVendor
		self.DeviceIDProduct = DeviceIDProduct
		self.DeviceIDVersion = DeviceIDVersion
		self.FileName = FileName
		
		# set the device type from above info
		self.setDeviceType()

############################
# GizmoDeviceType class end
##########################
