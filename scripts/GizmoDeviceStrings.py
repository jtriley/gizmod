    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script
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
# Version Information
##########################

# This covers all of the base scripts (ie those not in modules.d) users
# likely don't have to modify
VERSION_REQUIRED = 3.1

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

# List of devices to enumerate as mice
POWERMATE_GIZMOS = ["powermate", "soundknob"]

# Default mixer element preferences (in order of priority)
# Gizmo Daemon will scan all of the specified DEFAULT_MIXERS and apply the first
# one it finds from the list that has the needed control as the default mixing
# device.  Ie, If DEFAULT_MIXERS = ["master", "pcm"] then if the Master mixing 
# element has a playback volume, but no mute switch, and the PCM channel has 
# playback # volume and a mute switch, Gizmod.DefaultMixerVolume will be the 
# Master mixer, and Gizmod.DefaultMixerSwitch will be the PCM mixer.
DEFAULT_MIXERS = ["master", "pcm", "front", "center", "side", "surround", "headphones"]

# KEYBOARD_LEDS defines how the keyboard LED visualizer will use the LEDs
# The keyboard LEDs can be different on each keyboard, as there is no
# standard way of defining them set to hardware manufacturers. 
# Usually they are defined in this order:
# 	- Num Lock: 0
#	- Caps Lock: 1
#	- Scroll Lock: 2
# If your keyboard LEDs differ, simply change the following variable so that
# the first spot in the array points to the integer value of the "first"
# LED on your keyboard, the second spot in the array points to the "second"
# LED and so on.
KEYBOARD_LEDS = [0, 1, 2]
