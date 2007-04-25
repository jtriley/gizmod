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
				print "onEvent: " + str(Event.EventType) + " [" + str(Event.WindowEventType) + "] -- <WindowTitle:" + Event.WindowName + "> <FormalName:" + Event.WindowNameFormal + "> <Class:" + Event.WindowClass + ">"
			elif Event.Class == GizmoEventClass.LIRC:
				sys.stdout.write("onEvent: " + Event.EventType + " -- " + Gizmo.FileName + " | [" + str(len(Event.EventString)) + "]")
				for char in Event.EventString:
					sys.stdout.write(" " + str(ord(char)))
				sys.stdout.write("\n")
			else:
				if Event.Type == GizmoEventType.EV_KEY:
					print "onEvent: " + Event.EventType + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] <" + str(Event.Code) + "> c: " + str(hex(Event.RawCode)) + " v: " + str(hex(Event.Value))
				else:
					print "onEvent: " + Event.EventType + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] c: " + str(hex(Event.RawCode)) +  " Val: " + str(hex(Event.Value))					
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
Gizmod.Dispatcher.userScripts.append(CatchAllDebug())
