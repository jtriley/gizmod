    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	LIRCHauppauge Default config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *
from Hauppauge import *
import subprocess

ENABLED = True
INTERESTED_CLASSES = [GizmoEventClass.LIRC]
POWER_APPLICATION = "mythfrontend"

############################
# LIRCHauppaugeDefault Class definition
##########################

class LIRCHauppaugeDefault(Hauppauge):
	"""
	Default LIRC Event Mapping for the Hauppauge remote
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
		if Event.Class in INTERESTED_CLASSES and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	KeyString = self.getKeyString(Event)
		   	if KeyString == "Go":
		   		return False
		   	elif KeyString == "Power":
		   		if not Gizmod.isApplicationRunning(POWER_APPLICATION):
		   			subprocess.Popen([POWER_APPLICATION])
		   		return True
		   	elif KeyString == "TV":
		   		return False
		   	elif KeyString == "Videos":
		   		return False
		   	elif KeyString == "Music":
		   		return False
		   	elif KeyString == "Pictures":
		   		subprocess.Popen(["xset", "dpms", "force", "off"])
		   		return True
		   	elif KeyString == "Guide":
		   		return False
		   	elif KeyString == "Up":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
		   		return True
		   	elif KeyString == "Radio":
		   		return False
		   	elif KeyString == "Left":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
		   		return True
		   	elif KeyString == "OK":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
		   		return True
		   	elif KeyString == "Right":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
		   		return True
		   	elif KeyString == "Back/Exit":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
		   		return True
		   	elif KeyString == "Down":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
		   		return True
		   	elif KeyString == "Menu":
		   		return False
		   	elif KeyString == "VolUp":
		   		if Gizmod.DefaultMixerVolume:
		   			Gizmod.DefaultMixerVolume.VolumePlaybackPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent + 5
		   		return True
		   	elif KeyString == "VolDown":
		   		if Gizmod.DefaultMixerVolume:
		   			Gizmod.DefaultMixerVolume.VolumePlaybackPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent - 5
		   		return True
		   	elif KeyString == "Prev.Ch":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_BACKSPACE)
		   		return True
		   	elif KeyString == "Mute":
	   			Gizmod.toggleMuteAllCards()
		   		return True
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
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
		   		return True
		   	elif KeyString == "Skip":
		   		return False
		   	elif KeyString == "1":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_1)
		   		return True
		   	elif KeyString == "2":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_2)
		   		return True
		   	elif KeyString == "3":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_3)
		   		return True
		   	elif KeyString == "4":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_4)
		   		return True
		   	elif KeyString == "5":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_5)
		   		return True
		   	elif KeyString == "6":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_6)
		   		return True
		   	elif KeyString == "7":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_7)
		   		return True
		   	elif KeyString == "8":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_8)
		   		return True
		   	elif KeyString == "9":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_9)
		   		return True
		   	elif KeyString == "*":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTMETA, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_F12)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTMETA, 0)
		   		return True
		   	elif KeyString == "0":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_0)
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
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")

############################
# LIRCHauppaugeDefault class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(LIRCHauppaugeDefault())
