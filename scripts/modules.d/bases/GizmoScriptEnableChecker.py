    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	GizmoScript EnableChecker config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
import subprocess

############################
# GizmoScriptEnableChecker Class definition
##########################

class GizmoScriptEnableChecker:
	"""
	Base Class that checks whether or not a script should be enabled
	"""
	
	############################
	# Public Functions
	##########################
	
	############################
	# Private Functions
	##########################

	def __init__(self, Enabled, VersionNeeded):
		""" 
		EnableChecker Constructor
		"""
		
		self.Enabled = Enabled
		self.VersionNeeded = VersionNeeded
		
		if self.Enabled:
			if not Gizmod.checkVersion(self.VersionNeeded, False):
				Gizmod.printNiceScriptInit(1, " * " + self.__class__.__name__, "NOT LOADED", "Version Needed: " + str(self.VersionNeeded))
			else:
				Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")
				Gizmod.Dispatcher.userScripts.append(self)
		else:
			Gizmod.printNiceScriptInit(1, " * " + self.__class__.__name__, "NOT LOADED", "Disabled")

############################
# GizmoScriptEnableChecker class end
##########################
