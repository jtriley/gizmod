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

############################
# Version Information
##########################

# This covers all of the base scripts (ie those not in modules.d) users
# likely don't have to modify
VERSION_REQUIRED = 3.4

############################
# Device Strings
##########################

"""
This file contains defitions for what device strings get claimed as which devices
"""

# note all of the GIZMOS defines have the following properties:
# - they matches against the product description as seen when gizmod starts up
# - you can also put combinations of vendor / product ID codes in here
#   - example: "keyboard" will match any device with keyboard in its description
#   - example: "0x303:0x909" will math any device with Vendor ID: 0x303 
#     and Product ID: 0x909

# list of devices to enumerate as ATI X10 RF remotes
ATIX10_GIZMOS = ["x10 wireless technology"]

# List of devices to enumerate as keyboards
# this matches against the product description as seen when gizmod starts up
# note that you can also put combinations of vendor / product ID codes in here
#   - example: "keyboard" will match any device with keyboard in its description
#   - example: "0x303:0x909" will math any device with Vendor ID: 0x303 
#     and Product ID: 0x909
KEYBOARD_GIZMOS = ["keyboard"]

# List of devices to enumerate as mice
MOUSE_GIZMOS = ["mouse", "trackball", "touchpad"]

# list of devices to enumerate as ATI X10 RF remotes
LIRC_GIZMOS = ["lirc"]

# List of devices to enumerate as mice
POWERMATE_GIZMOS = ["powermate", "soundknob"]

# Powermate long click duration
POWERMATE_LONG_CLICK = 0.4

# Powermate button timeout duration
POWERMATE_BUTTON_TIMEOUT = 0.75

# Powermate rotate sensitivity
# This is done in clicks per event, so if it's set to 1 it's a one to 
# one mapping between events
# If it's set to 2 it take 2 rotate ticks to generate one event.
POWERMATE_ROTATE_SENSITIVITY = 1

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

# Time in seconds to timeout the Alt-Tab events
# Alt-Tabbing will stop after an Alt-Tab button press is not detected
# in this amount of time
ALT_TAB_TIMEOUT = 1.25
