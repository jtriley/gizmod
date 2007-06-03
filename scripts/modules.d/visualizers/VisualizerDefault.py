    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
#*** 	Visualizer Default config
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
import sys

VERSION_NEEDED = 3.1
INTERRUPT_LENGTH = 10

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
# VisualizerDefault Class definition
##########################

class VisualizerDefault:
	"""
	Keyboard Visualization Handler
	"""
	
	############################
	# Public Functions
	##########################
					
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
				self.applyVisualizationVolume()
				
			# check for switch changed
			if Event.SwitchPlaybackChanged \
			   and Gizmod.DefaultMixerSwitch \
			   and Event.Mixer.Name == Gizmod.DefaultMixerSwitch.Name:
				self.applyVisualizationVolume()
				
		# check for CPUUsage events
		elif self.Visualization == VisualizationType.CPUUsage \
		   and Event.Class == GizmoEventClass.CPUUsage\
		   and not (Gizmod.DefaultMixerSwitch and (not Gizmod.DefaultMixerSwitch.SwitchPlayback)):
		   	if not self.InterruptCount:
				self.applyVisualizationCPUUsage(Event)

		# check for Sound Visualization events
		elif self.Visualization == VisualizationType.SoundVisualization \
		   and Event.Class == GizmoEventClass.SoundVisualization \
		   and not (Gizmod.DefaultMixerSwitch and (not Gizmod.DefaultMixerSwitch.SwitchPlayback)):
		   	if not self.InterruptCount:
				self.applyVisualizationSound(Event)

		return False
					
	############################
	# Private Functions
	##########################
	
	def __init__(self):
		""" 
		Default Constructor
		"""

		# initialize member variables
		self.Visualization = VisualizationType.CPUUsage	# Current LED visualizer
		self.LastVis = self.Visualization		# Last known visualizer
		self.VolumeInterruptsOthers = True		# Set to True if volume changes should interrupt other visualizations
		self.InterruptCount = 0				# Length of time to remain interrupted
		self.SoundVisCount = 0				# Amarok is buggy and doesn't notify on exit, so this is the workaround
	
		# apply the initial visualization
		self.applyVisualizationVolume()

############################
# KeyboardVisualization class end
##########################
