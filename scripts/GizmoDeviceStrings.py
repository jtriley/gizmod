    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	GizmoDeviceStrings.py
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

############################
# Device Strings
##########################

"""
This file contains defitions for what device strings get claimed as which devices
"""

# list of devices to enumerate as ATI X10 RF remotes
ATIX10_GIZMOS = ["x10 wireless technology"]

# List of devices to enumerate as keyboards
KEYBOARD_GIZMOS = ["keyboard"]

# List of devices to enumerate as mice
MOUSE_GIZMOS = ["mouse", "trackball", "touchpad", "logitech usb receiver"]

# list of devices to enumerate as ATI X10 RF remotes
LIRC_GIZMOS = ["lirc"]

# list of lirc remotes -- these should match their class name in modules.d/devices.lirc
LIRC_REMOTES = ["Hauppauge", "MceUSB2"]

# List of devices to enumerate as mice
POWERMATE_GIZMOS = ["powermate", "soundknob"]

# Default mixer element preferences (in order of priority)
# Gizmo Daemon will scan all of the specified DEFAULT_MIXERS and apply the first
# one it finds from the list that has the needed control as the default mixing
# device.  Ie, If DEFAULT_MIXERS = ["master", "pcm"] then if the Master mixing 
# element has a playback volume, but no mute switch, and the PCM channel has 
# playback # volume and a mute switch, Gizmod.DefaultMixerVolume will be the 
# Master mixer, and Gizmod.DefaultMixerSwitch will be the PCM mixer.
DEFAULT_MIXERS = ["master", "pcm", "front", "center", "side", "surround"]

