    #***
  #*********************************************************************
#*************************************************************************
#***
#*** GizmoDaemon User Config Script
#***    GizmodUser.py
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

# This file is executed after Gizmod.py and can be thought of as having
# been included after that file's execution.  The following environment 
# is available in this file:
#
# - The GizmoDaemon namespace is already imported
# - There exists an object "Gizmod" that is the main program core
# - There exists an object "Dispatcher" that is defined in Gizmod.py as 
#   class GizmodDispatcher

#print
#print "From Python to C++ Gizmod Version v" + str(Gizmod.getVersion())
#print "Dispatcher Initialized from Python: " + str(Dispatcher.getInitialized())
#print 
