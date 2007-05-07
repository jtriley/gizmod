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

# tehe lirc remote names that work with this mapping
REMOTE_NAMES = ["mceusb", "mceusb2"]

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

		# ensure that the code is for this remote
		if Event.Remote not in REMOTE_NAMES:
			return None
		
		# parse the data
		if   Event.Code == 0xbb: return "Go"
		elif Event.Code == 0xbd: return "Power"
		elif Event.Code == 0x9c: return "TV"
		elif Event.Code == 0x98: return "Videos"
		elif Event.Code == 0x99: return "Music"
		elif Event.Code == 0x9a: return "Pictures"
		elif Event.Code == 0x9b: return "Guide"
		elif Event.Code == 0x94: return "Up"
		elif Event.Code == 0x8c: return "Radio"
		elif Event.Code == 0x96: return "Left"
		elif Event.Code == 0xa5: return "OK"
		elif Event.Code == 0x97: return "Right"
		elif Event.Code == 0x9f: return "Back/Exit"
		elif Event.Code == 0x95: return "Down"
		elif Event.Code == 0x8d: return "Menu"
		elif Event.Code == 0x90: return "VolUp"
		elif Event.Code == 0x91: return "VolDown"
		elif Event.Code == 0x92: return "Prev.Ch"
		elif Event.Code == 0x8f: return "Mute"
		elif Event.Code == 0xa0: return "ChUp"
		elif Event.Code == 0xa1: return "ChDown"
		elif Event.Code == 0xb7: return "Rec"
		elif Event.Code == 0xb6: return "Stop"
		elif Event.Code == 0xb2: return "Rewind"
		elif Event.Code == 0xb5: return "Play"
		elif Event.Code == 0xb4: return "FastForward"
		elif Event.Code == 0xa4: return "Replay"
		elif Event.Code == 0xb0: return "Pause"
		elif Event.Code == 0x9e: return "Skip"
		elif Event.Code == 0x81: return "1"
		elif Event.Code == 0x82: return "2"
		elif Event.Code == 0x83: return "3"
		elif Event.Code == 0x84: return "4"
		elif Event.Code == 0x85: return "5"
		elif Event.Code == 0x86: return "6"
		elif Event.Code == 0x87: return "7"
		elif Event.Code == 0x88: return "8"
		elif Event.Code == 0x89: return "9"
		elif Event.Code == 0x8a: return "*"
		elif Event.Code == 0x80: return "0"
		elif Event.Code == 0x8e: return "#"
		elif Event.Code == 0x8b: return "Red"
		elif Event.Code == 0xae: return "Green"
		elif Event.Code == 0xb8: return "Yellow"
		elif Event.Code == 0xa9: return "Blue"
		else:
			return None
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		pass

############################
# MceUSB2 class end
##########################
