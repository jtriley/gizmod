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
import subprocess

ENABLED = True
USES_LIRC_REMOTES = ["Hauppauge_350"]
INTERESTED_CLASSES = [GizmoEventClass.LIRC]

############################
# LIRCHauppaugeDefault Class definition
##########################

class LIRCHauppaugeDefault:
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
		if Event.Class in INTERESTED_CLASSES and Event.Remote in USES_LIRC_REMOTES \
		   and len(Gizmod.Mice) and len(Gizmod.Keyboards):
			# process the key
		   	if   Event.Button == "Go":
		   		return False
		   	elif Event.Button == "Power":
		   		return False
		   	elif Event.Button == "TV":
		   		return False
		   	elif Event.Button == "Videos":
		   		return False
		   	elif Event.Button == "Music":
		   		return False
		   	elif Event.Button == "Pictures":
		   		subprocess.Popen(["xset", "dpms", "force", "off"])
		   		return True
		   	elif Event.Button == "Guide":
		   		return False
		   	elif Event.Button == "Up":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_UP)
		   		return True
		   	elif Event.Button == "Radio":
		   		return False
		   	elif Event.Button == "Left":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFT)
		   		return True
		   	elif Event.Button == "OK":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ENTER)
		   		return True
		   	elif Event.Button == "Right":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_RIGHT)
		   		return True
		   	elif Event.Button == "Back/Exit":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_ESC)
		   		return True
		   	elif Event.Button == "Down":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_DOWN)
		   		return True
		   	elif Event.Button == "Menu/i":
		   		return False
		   	elif Event.Button == "Vol+":
		   		if Gizmod.DefaultMixerVolume:
		   			Gizmod.DefaultMixerVolume.VolumePlaybackPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent + 2.5
		   		return True
		   	elif Event.Button == "Vol-":
		   		if Gizmod.DefaultMixerVolume:
		   			Gizmod.DefaultMixerVolume.VolumePlaybackPercent = Gizmod.DefaultMixerVolume.VolumePlaybackPercent - 2.5
		   		return True
		   	elif Event.Button == "Prev.Ch":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_BACKSPACE)
		   		return True
		   	elif Event.Button == "Mute":
	   			Gizmod.toggleMuteAllCards()
		   		return True
		   	elif Event.Button == "Ch+":
		   		return False
		   	elif Event.Button == "Ch-":
		   		return False
		   	elif Event.Button == "Record":
		   		return False
		   	elif Event.Button == "Stop":
		   		return False
		   	elif Event.Button == "Rewind":
		   		return False
		   	elif Event.Button == "Play":
		   		return False
		   	elif Event.Button == "Forward":
		   		return False
		   	elif Event.Button == "Replay/SkipBackward":
		   		return False
		   	elif Event.Button == "Pause":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_P)
		   		return True
		   	elif Event.Button == "SkipForward":
		   		return False
		   	elif Event.Button == "1":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_1)
		   		return True
		   	elif Event.Button == "2":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_2)
		   		return True
		   	elif Event.Button == "3":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_3)
		   		return True
		   	elif Event.Button == "4":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_4)
		   		return True
		   	elif Event.Button == "5":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_5)
		   		return True
		   	elif Event.Button == "6":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_6)
		   		return True
		   	elif Event.Button == "7":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_7)
		   		return True
		   	elif Event.Button == "8":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_8)
		   		return True
		   	elif Event.Button == "9":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_9)
		   		return True
		   	elif Event.Button == "Asterix":
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTMETA, 1)
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_F12)
				Gizmod.Keyboards[0].createEvent(GizmoEventType.EV_KEY, GizmoKey.KEY_LEFTMETA, 0)
		   		return True
		   	elif Event.Button == "0":
				Gizmod.Keyboards[0].createEventPress(GizmoEventType.EV_KEY, GizmoKey.KEY_0)
		   		return True
		   	elif Event.Button == "#":
		   		return False
		   	elif Event.Button == "Red":
		   		return False
		   	elif Event.Button == "Green":
		   		return False
		   	elif Event.Button == "Yellow":
		   		return False
		   	elif Event.Button == "Blue":
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
		
		Gizmod.printNiceScriptInit(1, self.__class__.__name__, self.__class__.__doc__, "")

############################
# LIRCHauppaugeDefault class end
##########################

# register the user script
if ENABLED:
	Gizmod.Dispatcher.userScripts.append(LIRCHauppaugeDefault())
