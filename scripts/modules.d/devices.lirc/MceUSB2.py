    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	MceUSB2 config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from LIRCUtil import *

TOLERANCE = 0.05

############################
# MceUSB2 Button definitions
##########################

POWER0 = [0xc2, 0x1, 0x0, 0x0, 0xc2, 0x1, 0x0, 0x1]
POWER1 = [0x90, 0x1, 0x0, 0x0, 0xf4, 0x1, 0x0, 0x1]
MYTV0  = [0x52, 0x3, 0x0, 0x0, 0xf4, 0x1, 0x0, 0x1]
MYTV1  = [0x52, 0x3, 0x0, 0x0, 0xc2, 0x1, 0x0, 0x1]

############################
# MceUSB2 Class definition
##########################

class MceUSB2:
	"""
	MceUSB2 Event mapping
	"""
	
	############################
	# Public Functions
	##########################
	
	def getKeyString(self, Event):
		"""
		Get a human friendly key name from the key code
		"""
		return None
		# ensure that the code is valid
		if len(Event.LIRCData) != 8:
			return None
		elif self.LIRCUtil.doesCodeMatch(POWER0, Event.LIRCData): return "Power"
		elif self.LIRCUtil.doesCodeMatch(POWER1, Event.LIRCData): return "Power"
		elif self.LIRCUtil.doesCodeMatch(MYTV0,  Event.LIRCData): return "MyTV"
		else:
			return None
		"""
		# parse the data
		if   data2 == 0xbb: return "Go"
		elif data2 == 0xbd: return "Power"
		elif data2 == 0x9c: return "TV"
		elif data2 == 0x98: return "Videos"
		elif data2 == 0x99: return "Music"
		elif data2 == 0x9a: return "Pictures"
		elif data2 == 0x9b: return "Guide"
		elif data2 == 0x94: return "Up"
		elif data2 == 0x8c: return "Radio"
		elif data2 == 0x96: return "Left"
		elif data2 == 0xa5: return "OK"
		elif data2 == 0x97: return "Right"
		elif data2 == 0x9f: return "Back/Exit"
		elif data2 == 0x95: return "Down"
		elif data2 == 0x8d: return "Menu"
		elif data2 == 0x90: return "VolUp"
		elif data2 == 0x91: return "VolDown"
		elif data2 == 0x92: return "Prev.Ch"
		elif data2 == 0x8f: return "Mute"
		elif data2 == 0xa0: return "ChUp"
		elif data2 == 0xa1: return "ChDown"
		elif data2 == 0xb7: return "Rec"
		elif data2 == 0xb6: return "Stop"
		elif data2 == 0xb2: return "Rewind"
		elif data2 == 0xb5: return "Play"
		elif data2 == 0xb4: return "FastForward"
		elif data2 == 0xa4: return "Replay"
		elif data2 == 0xb0: return "Pause"
		elif data2 == 0x9e: return "Skip"
		elif data2 == 0x81: return "1"
		elif data2 == 0x82: return "2"
		elif data2 == 0x83: return "3"
		elif data2 == 0x84: return "4"
		elif data2 == 0x85: return "5"
		elif data2 == 0x86: return "6"
		elif data2 == 0x87: return "7"
		elif data2 == 0x88: return "8"
		elif data2 == 0x89: return "9"
		elif data2 == 0x8a: return "*"
		elif data2 == 0x80: return "0"
		elif data2 == 0x8e: return "#"
		elif data2 == 0x8b: return "Red"
		elif data2 == 0xae: return "Green"
		elif data2 == 0xb8: return "Yellow"
		elif data2 == 0xa9: return "Blue"
		else:
			return None
		"""
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		self.LIRCUtil = LIRCUtil(TOLERANCE)

############################
# MceUSB2 class end
##########################
