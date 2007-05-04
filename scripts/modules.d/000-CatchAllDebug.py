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

ENABLED = True

############################
# CatchAllDebug Class definition
##########################

class CatchAllDebug:
	"""
	CatchAll Event Mapping for Testing
	"""
	
	############################
	# Public Functions
	##########################
	
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
	
		# if debug mode isn't enabled, don't bother!
		if not Gizmod.DebugEnabled:
			return False

		# debug mode enabled so print the event
		if Event.Class == GizmoEventClass.WindowFocus:
			print "onEvent: " + str(Event.Class) + " [" + str(Event.WindowEventType) + "] -- <WindowTitle:" + Event.WindowName + "> <FormalName:" + Event.WindowNameFormal + "> <Class:" + Event.WindowClass + ">"
		elif Event.Class == GizmoEventClass.LIRC:
			sys.stdout.write("onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(len(Event.LIRCData)) + "]")
			for char in Event.LIRCData:
				sys.stdout.write(" " + str(hex(ord(char))))
			sys.stdout.write(" | " + Event.LIRCDataBitString)
			sys.stdout.write("\n")
		elif Event.Class == GizmoEventClass.SoundCard:
			if Event.Mixer:
				sys.stdout.write("onEvent: " + str(Event.Class) + " -- " + str(Event.Type) + " [" + str(Event.SoundCard.CardName) + "] <" + str(Event.Mixer.Name) + ">")
				if Event.VolumePlaybackChanged:
					sys.stdout.write(" Vol: " + str(Event.Mixer.VolumePlaybackPercent))
				if Event.SwitchPlaybackChanged:
					if Event.Mixer.SwitchPlayback:
						sys.stdout.write(" Unmute")
					else:
						sys.stdout.write(" Mute")
				sys.stdout.write("\n")
			else:
				print "onEvent: " + str(Event.Class) + " -- " + str(Event.Type) + " [" + str(Event.SoundCard.CardName) + "]"
		elif Event.Class == GizmoEventClass.CPUUsage:
			print "onEvent: " + str(Event.Class) + " -- " + str(Event.getCPUUsage(0)) + " [" + str(Event.getCPUUsageAvg(0)) + "]"
		else:
			if Event.Type == GizmoEventType.EV_KEY:
				print "onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] <" + str(Event.Code) + "> c: " + str(hex(Event.RawCode)) + " v: " + str(hex(Event.Value))
			else:
				print "onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] c: " + str(hex(Event.RawCode)) +  " Val: " + str(hex(Event.Value))					
				
		# return False always so that events continue to get processed by other scripts
		return False
			
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")

############################
# CatchAllDebug class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(CatchAllDebug())
