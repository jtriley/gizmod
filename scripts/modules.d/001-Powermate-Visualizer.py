    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	Powermate Visualization config
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
INTERRUPT_LENGTH = 10

############################
# Visualization Class definition
##########################

class VisualizationType:
	"""
	Types of visualizations
	"""
	
	CPUUsage = "CPUUsage"
	Volume = "Volume"

############################
# PowermateVisualizer Class definition
##########################

class PowermateVisualizer:
	"""
	Powermate Visualization Handler
	"""
	
	############################
	# Public Functions
	##########################
	
	def applyVisualization(self):
		"""
		Apply the current visualization type to the Powermate's LED
		"""

		if self.Visualization == VisualizationType.Volume:
			self.__applyVisualizationVolume()
				
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
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
		   	if self.InterruptCount:
		   		self.InterruptCount -= 1
		   	else:
				self.__applyVisualizationCPUUsage(Event)

		return False
					
	############################
	# Private Functions
	##########################
	
	def __applyVisualizationCPUUsage(self, Event):
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
		
	def __applyVisualizationVolume(self):
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
			

	def __init__(self):
		""" 
		Default Constructor
		"""

		# print informative text		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, str(len(Gizmod.Powermates)) + " Powermates")

		# initialize member variables
		self.Visualization = VisualizationType.CPUUsage	# Current LED visualizer
		self.VolumeInterruptsOthers = True		# Set to True if volume changes should interrupt other visualizations
		self.InterruptCount = 0				# Length of time to remain interrupted
		
		# apply the initial visualization
		self.applyVisualization()

############################
# PowermateVisualization class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(PowermateVisualizer())
