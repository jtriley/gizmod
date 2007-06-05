    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	CatchAll Debug config
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
from GizmoScriptEnableChecker import *
import sys

ENABLED = True
VERSION_NEEDED = 3.2

############################
# CatchAllDebug Class definition
##########################

class CatchAllDebug(GizmoScriptEnableChecker):
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
		
		# check if it's a remote event
		if Event.Remote:
			sys.stdout.write("[R] ")
		
		# debug mode enabled so print the event
		if Event.Class == GizmoEventClass.WindowFocus:
			print "onEvent: " + str(Event.Class) + " [" + str(Event.WindowEventType) + "] -- <WindowTitle:" + Event.WindowName + "> <FormalName:" + Event.WindowNameFormal + "> <Class:" + Event.WindowClass + ">"
		elif Event.Class == GizmoEventClass.LIRC:
			print "onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + Event.Code + "] " + Event.Button + " <" + Event.Remote + "> Repeat: " + str(Event.Repeat)
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
			#for lp in range(Event.NumCPUs):
			#	print "onEvent: " + str(Event.Class) + " [" + str(lp) + "] " + str(Event.getCPUUsage(lp)) + " -- " + str(Event.getCPUUsageAvg(lp))
			pass
		elif Event.Class == GizmoEventClass.Powermate and Event.Type == GizmoEventType.EV_MSC:
			# Don't print LED change events
			pass
		elif Event.Class == GizmoEventClass.SoundVisualization:
			#print "onEvent: " + str(Event.Class) + " [" + str(Event.Type) + "] -- L: " + str(Event.VULeft) + " R: " + str(Event.VURight) + " C: " + str(Event.VUCombined)
			pass
		else:
			if Event.Type == GizmoEventType.EV_KEY:
				if Event.Class == GizmoEventClass.Powermate and Event.Value == 0:
					print "onEvent: " + str(Event.Class) + " -- " + Gizmo.FileName + " | [" + str(Event.Type) + "] <" + str(Event.Code) + "> c: " + str(hex(Event.RawCode)) + " v: " + str(hex(Event.Value)) + " Duration: " + str(Event.ClickTime)
				else:
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

		GizmoScriptEnableChecker.__init__(self, ENABLED, VERSION_NEEDED)

############################
# CatchAllDebug class end
##########################

# register the user script
CatchAllDebug()
