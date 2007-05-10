    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Powermate Visualization config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from GizmoDeviceStrings import *
from VisualizerDefault import *
import sys

ENABLED = True
VERSION_NEEDED = 3.1

############################
# PowermateVisualizer Class definition
##########################

class PowermateVisualizer(VisualizerDefault):
	"""
	Powermate Visualization Handler
	"""
	
	############################
	# Public Functions
	##########################

	def applyVisualizationCPUUsage(self, Event):
		"""
		Set the Powermates' LEDs to the current system CPU Usage
		"""
		
		Count = 0
		for Powermate in Gizmod.Powermates:
			if Count >= Event.NumCPUs:
				Count = 0
			else:
				Count += 1
			Powermate.LEDPercent = Event.getCPUUsageAvg(Count)
		
	def applyVisualizationVolume(self):
		"""
		Set the Powermates' LEDs to the Default playback volume mixer's level
		"""

		# make sure there's a mixer available		
		if not Gizmod.DefaultMixerVolume:
			return
			
		# update the Powermates' LEDs
		if Gizmod.DefaultMixerSwitch.SwitchPlayback:
			# if not muted set LED to volume level
			for Powermate in Gizmod.Powermates:
				Powermate.LEDPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent	
		else:
			# if muted pulse the led
			for Powermate in Gizmod.Powermates:
				Powermate.pulseLED(255, 257, 2)
			
	def applyVisualizationSound(self, Event):
		"""
		Set the Powermates' LEDs to the sound level
		"""
		
		if len(Gizmod.Powermates) == 1:
			Gizmod.Powermates[0].LEDPercent = Event.VUCombined * 100.0
		else:
			Gizmod.Powermates[0].LEDPercent = Event.VULeft * 100.0
			Gizmod.Powermates[1].LEDPercent = Event.VURight * 100.0

	############################
	# Private Functions
	##########################
	
	def __init__(self):
		""" 
		Default Constructor
		"""
		
		# call base constructor
		VisualizerDefault.__init__(self)

		# print informative text		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, str(len(Gizmod.Powermates)) + " Powermates")

############################
# PowermateVisualization class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * PowermateVisualizer", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(PowermateVisualizer())
