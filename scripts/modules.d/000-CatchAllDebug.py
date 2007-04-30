    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	CatchAll Debug config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
import sys

ENABLED=True

############################
# CatchAllDebug Class definition
##########################

class CatchAllDebug:
	"""
	CatchAll Event mapping
	"""
	
	############################
	# Public Functions
	##########################
	
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
	
		if Gizmod.DebugEnabled:
			if Event.Class == GizmoEventClass.WindowFocus:
				print "onEvent: " + str(Event.Class) + " [" + str(Event.WindowEventType) + "] -- <WindowTitle:" + Event.WindowName + "> <FormalName:" + Event.WindowNameFormal + "> <Class:" + Event.WindowClass + ">"
			elif Event.Class == GizmoEventClass.LIRC:
				sys.stdout.write("onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(len(Event.LIRCData)) + "]")
				for char in Event.LIRCData:
					sys.stdout.write(" " + str(hex(ord(char))))
				sys.stdout.write(" | " + Event.LIRCDataBitString)
				sys.stdout.write("\n")
			else:
				if Event.Type == GizmoEventType.EV_KEY:
					print "onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] <" + str(Event.Code) + "> c: " + str(hex(Event.RawCode)) + " v: " + str(hex(Event.Value))
				else:
					print "onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] c: " + str(hex(Event.RawCode)) +  " Val: " + str(hex(Event.Value))					
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
# CatchAllDebug class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(CatchAllDebug())
