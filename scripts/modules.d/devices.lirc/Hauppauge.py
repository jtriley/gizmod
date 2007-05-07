    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	Hauppauge config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

# tehe lirc remote names that work with this mapping
REMOTE_NAMES = ["Hauppauge_350"]

############################
# Hauppauge Class definition
##########################

class Hauppauge:
	"""
	Hauppauge Event mapping
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
		if   Event.Code == 0x17bb: return "Go"
		elif Event.Code == 0x17bd: return "Power"
		elif Event.Code == 0x179c: return "TV"
		elif Event.Code == 0x1798: return "Videos"
		elif Event.Code == 0x1799: return "Music"
		elif Event.Code == 0x179a: return "Pictures"
		elif Event.Code == 0x179b: return "Guide"
		elif Event.Code == 0x1794: return "Up"
		elif Event.Code == 0x178c: return "Radio"
		elif Event.Code == 0x1796: return "Left"
		elif Event.Code == 0x17a5: return "OK"
		elif Event.Code == 0x1797: return "Right"
		elif Event.Code == 0x179f: return "Back/Exit"
		elif Event.Code == 0x1795: return "Down"
		elif Event.Code == 0x178d: return "Menu"
		elif Event.Code == 0x1790: return "VolUp"
		elif Event.Code == 0x1791: return "VolDown"
		elif Event.Code == 0x1792: return "Prev.Ch"
		elif Event.Code == 0x178f: return "Mute"
		elif Event.Code == 0x17a0: return "ChUp"
		elif Event.Code == 0x17a1: return "ChDown"
		elif Event.Code == 0x17b7: return "Rec"
		elif Event.Code == 0x17b6: return "Stop"
		elif Event.Code == 0x17b2: return "Rewind"
		elif Event.Code == 0x17b5: return "Play"
		elif Event.Code == 0x17b4: return "FastForward"
		elif Event.Code == 0x17a4: return "Replay"
		elif Event.Code == 0x17b0: return "Pause"
		elif Event.Code == 0x179e: return "Skip"
		elif Event.Code == 0x1781: return "1"
		elif Event.Code == 0x1782: return "2"
		elif Event.Code == 0x1783: return "3"
		elif Event.Code == 0x1784: return "4"
		elif Event.Code == 0x1785: return "5"
		elif Event.Code == 0x1786: return "6"
		elif Event.Code == 0x1787: return "7"
		elif Event.Code == 0x1788: return "8"
		elif Event.Code == 0x1789: return "9"
		elif Event.Code == 0x178a: return "*"
		elif Event.Code == 0x1780: return "0"
		elif Event.Code == 0x178e: return "#"
		elif Event.Code == 0x178b: return "Red"
		elif Event.Code == 0x17ae: return "Green"
		elif Event.Code == 0x17b8: return "Yellow"
		elif Event.Code == 0x17a9: return "Blue"
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
# Hauppauge class end
##########################
