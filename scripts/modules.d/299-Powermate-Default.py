    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	Powermate Default config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

ENABLED=True

############################
# PowermateDefault Class definition
##########################

class PowermateDefault:
	"""
	Default Event mapping for the Powermate
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""

		return False
		
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		print "Loaded User Script: " + self.__class__.__name__

############################
# PowermateDefault class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(PowermateDefault())
