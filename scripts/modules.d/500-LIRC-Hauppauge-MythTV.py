    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	LIRCHauppauge MythTV config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from Hauppauge import *

ENABLED = True
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
INTERESTED_WINDOWS = ["mythfrontend"]

############################
# LIRCHauppaugeMythTV Class definition
##########################

class LIRCHauppaugeMythTV(Hauppauge):
	"""
	Event mapping for LIRC when using MythTV with the Hauppauge remote
	"""
	
	############################
	# Public Functions
	##########################
			
	def onEvent(self, Event, Gizmo = None):
		"""
		See GizmodDispatcher.onEvent documention for an explanation of this function
		"""
		
		# if the event class is in INTERESTED_CLASSES and the active window is
		# one of INTERESTED_WINDOWS and there is a keyboard and mouse attached 
		# then process the event
		if Event.Class in INTERESTED_CLASSES and \
		   [i for i in INTERESTED_WINDOWS if Gizmod.CurrentFocus.WindowName.lower().find(i) > -1] and \
		   len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	KeyString = self.getKeyString(Event)
		   	if KeyString == "Go":
		   		return False
		   	elif KeyString == "Power":
		   		# start mythfront end if power button pressed
		   		# if mythfrontend is open, kill it
		   		if Gizmod.isApplicationRunning("mythfrontend"):
		   			subprocess.Popen(["mythfrontend"])
		   		else:
		   			subprocess.Popen(["killall", "mythfrontend"])
		   		return False
		   	elif KeyString == "TV":
		   		return False
		   	elif KeyString == "Videos":
		   		return False
		   	elif KeyString == "Music":
		   		return False
		   	elif KeyString == "Pictures":
		   		return False
		   	elif KeyString == "Guide":
		   		return False
		   	elif KeyString == "Up":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_UP, 0)
		   		return True
		   	elif KeyString == "Radio":
		   		return False
		   	elif KeyString == "Left":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT, 0)
		   		return True
		   	elif KeyString == "OK":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER, 0)
		   		return True
		   	elif KeyString == "Right":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT, 0)
		   		return True
		   	elif KeyString == "Back/Exit":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESCAPE, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_ESCAPE, 0)
		   		return True
		   	elif KeyString == "Down":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN, 0)
		   		return True
		   	elif KeyString == "Menu":
		   		return False
		   	elif KeyString == "VolUp":
		   		return False
		   	elif KeyString == "VolDown":
		   		return False
		   	elif KeyString == "Prev.Ch":
		   		return False
		   	elif KeyString == "Mute":
		   		return False
		   	elif KeyString == "ChUp":
		   		return False
		   	elif KeyString == "ChDown":
		   		return False
		   	elif KeyString == "Rec":
		   		return False
		   	elif KeyString == "Stop":
		   		return False
		   	elif KeyString == "Rewind":
		   		return False
		   	elif KeyString == "Play":
		   		return False
		   	elif KeyString == "FastForward":
		   		return False
		   	elif KeyString == "Replay":
		   		return False
		   	elif KeyString == "Pause":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_P, 0)
		   		return True
		   	elif KeyString == "Skip":
		   		return False
		   	elif KeyString == "1":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_1, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_1, 0)
		   		return True
		   	elif KeyString == "2":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_2, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_2, 0)
		   		return True
		   	elif KeyString == "3":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_3, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_3, 0)
		   		return True
		   	elif KeyString == "4":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_4, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_4, 0)
		   		return True
		   	elif KeyString == "5":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_5, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_5, 0)
		   		return True
		   	elif KeyString == "6":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_6, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_6, 0)
		   		return True
		   	elif KeyString == "7":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_7, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_7, 0)
		   		return True
		   	elif KeyString == "8":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_8, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_8, 0)
		   		return True
		   	elif KeyString == "9":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_9, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_9, 0)
		   		return True
		   	elif KeyString == "*":
		   		return False
		   	elif KeyString == "0":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_0, 1)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_0, 0)
		   		return True
		   	elif KeyString == "#":
		   		return False
		   	elif KeyString == "Red":
		   		return False
		   	elif KeyString == "Green":
		   		return False
		   	elif KeyString == "Yellow":
		   		return False
		   	elif KeyString == "Blue":
		   		return False
		   	else:
		   		# unmatched event, keep processing
				return False				
		# event not of interest
		return False
	
	############################
	# Private Functions
	##########################

	def __init__(self):
		""" 
		Default Constructor
		"""
		
		Hauppauge.__init__(self)
		print "Loaded User Script: " + self.__class__.__name__

############################
# LIRCHauppaugeMythTV class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(LIRCHauppaugeMythTV())
