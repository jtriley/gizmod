    #***
  #*********************************************************************
#*************************************************************************
#***
#*** GizmoDaemon User Config Script v3:0
#***    User.py
#***
#*****************************************
  #*****************************************
    #***

# This file is executed after Gizmod.py and can be thought of as having
# been included after that file's execution.  The following environment 
# is available in this file:
#
# - The GizmoDaemon namespace is already imported
# - There exists an object "Gizmod" that is the main program core
# - There exists an object "Dispatcher" that is defined in Gizmod.py as 
#   class GizmodDispatcher
# - Dispatcher has already had its "__construct__" and "initialize" 
#   methods called

print
print "From Python to C++ Gizmod Version v" + str(Gizmod.getVersion())
print "Dispatcher Initialized from Python: " + str(Dispatcher.getInitialized())
print 
print "Powermate test: " + str(Gizmod.getLEDValue())
