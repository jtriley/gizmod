    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Keyboard Visualization config
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
VERSION_NEEDED = 3.0
INTERRUPT_LENGTH = 10
LEDS = [2, 1, 0]

############################
# Visualization Class definition
##########################

class VisualizationType:
	"""
	Types of visualizations
	"""
	
	CPUUsage = 		"CPUUsage"
	SoundVisualization = 	"SoundVisualization"
	Volume = 		"Volume"

############################
# KeyboardVisualizer Class definition
##########################

class KeyboardVisualizer:
	"""
	Keyboard Visualization Handler
	"""
	
	############################
	# Public Functions
	##########################
	
	def applyVisualization(self):
		"""
		Apply the current visualization type to the Keyboard's LED
		"""

		if self.Visualization == VisualizationType.Volume:
			self.__applyVisualizationVolume()
				
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# take care of the interrupt count
		if Event.Class == GizmoEventClass.CPUUsage:
			if self.InterruptCount:
				self.InterruptCount -= 1
			if self.SoundVisCount:
				self.SoundVisCount -= 1
				if not self.SoundVisCount:
					self.Visualization = self.LastVis
		
		# take care of the interrupt count
		if Event.Class == GizmoEventClass.SoundVisualization:
			if Event.Type == SoundVisualizationEventType.Connect:
				self.LastVis = self.Visualization
			self.Visualization = VisualizationType.SoundVisualization
			self.SoundVisCount = INTERRUPT_LENGTH
		
		# check for mixer events
		if (self.Visualization == VisualizationType.Volume or self.VolumeInterruptsOthers) \
		   and Event.Class == GizmoEventClass.SoundCard \
		   and Event.Type == AlsaEventType.MixerElementChange:
		   	# if we're an interruption, mark the occasion
		   	self.InterruptCount = INTERRUPT_LENGTH
		   	
		   	# check for volume changed
			if Event.VolumePlaybackChanged \
			   and Gizmod.DefaultMixerVolume \
			   and Event.Mixer.Name == Gizmod.DefaultMixerVolume.Name:
				self.__applyVisualizationVolume()
				
			# check for switch changed
			if Event.SwitchPlaybackChanged \
			   and Gizmod.DefaultMixerSwitch \
			   and Event.Mixer.Name == Gizmod.DefaultMixerSwitch.Name:
				self.__applyVisualizationVolume()
				
		# check for CPUUsage events
		elif self.Visualization == VisualizationType.CPUUsage \
		   and Event.Class == GizmoEventClass.CPUUsage\
		   and not (Gizmod.DefaultMixerSwitch and (not Gizmod.DefaultMixerSwitch.SwitchPlayback)):
		   	if not self.InterruptCount:
				self.__applyVisualizationCPUUsage(Event)

		# check for Sound Visualization events
		elif self.Visualization == VisualizationType.SoundVisualization \
		   and Event.Class == GizmoEventClass.SoundVisualization \
		   and not (Gizmod.DefaultMixerSwitch and (not Gizmod.DefaultMixerSwitch.SwitchPlayback)):
		   	if not self.InterruptCount:
				self.__applyVisualizationSound(Event)

		return False
					
	############################
	# Private Functions
	##########################
	
	def __setLEDsPercent(self, Percent):
		"""
		Set the keyboard LEDs to a percentage
		"""
		
		CurVal = 0
		for i in range(len(LEDS)):
			if Percent >= CurVal and Percent >= 10.0:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_LED, LEDS[i], 1)
			else:
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_LED, LEDS[i], 0)
			CurVal += self.RangePerLED	
	
	def __applyVisualizationCPUUsage(self, Event):
		"""
		Set the Keyboards' LEDs to the current system CPU Usage
		"""
		
		self.__setLEDsPercent(Event.getCPUUsageAvg(0))
		
	def __applyVisualizationVolume(self):
		"""
		Set the Keyboards' LEDs to the Default playback volume mixer's level
		"""

		# make sure there's a mixer available		
		if not Gizmod.DefaultMixerVolume:
			return
			
		# update the Keyboards' LEDs
		if Gizmod.DefaultMixerSwitch.SwitchPlayback:
			# if not muted set LED to volume level
			self.__setLEDsPercent(Gizmod.DefaultMixerVolume.VolumePlaybackPercent)
		else:
			# if muted pulse the led
			for i in range(len(LEDS)):
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_LED, i, 0)
			
	def __applyVisualizationSound(self, Event):
		"""
		Set the Keyboards' LEDs to the sound level
		"""
		
		self.__setLEDsPercent(Event.VUCombined * 100.0)

	def __init__(self):
		""" 
		Default Constructor
		"""

		# print informative text		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, str(len(Gizmod.Keyboards)) + " Keyboards")

		# initialize member variables
		self.Visualization = VisualizationType.CPUUsage	# Current LED visualizer
		self.LastVis = self.Visualization		# Last known visualizer
		self.VolumeInterruptsOthers = True		# Set to True if volume changes should interrupt other visualizations
		self.InterruptCount = 0				# Length of time to remain interrupted
		self.SoundVisCount = 0				# Amarok is buggy and doesn't notify on exit, so this is the workaround
		self.RangePerLED = 100.0 / float(len(LEDS))
		
		# apply the initial visualization
		self.applyVisualization()

############################
# KeyboardVisualization class end
##########################

# register the user script
if ENABLED:
	if not Gizmod.checkVersion(VERSION_NEEDED, False):
		Gizmod.printNiceScriptInit(1, " * KeyboardVisualizer", "NOT LOADED", "Version Needed: " + str(VERSION_NEEDED))
	else:
		Gizmod.Dispatcher.userScripts.append(KeyboardVisualizer())
