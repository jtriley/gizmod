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
# been included after that file's execution
#
# The GizmoDaemon namespace is already imported
# There exists an object "Gizmod" that is the main program core
# There exists an object "Dispatcher" that is defined in Gizmod.py as type 
#    GizmodDispatcher
# Dispatcher has already had its "initialize" method called

print
print "From Python to C++ Gizmod Version v" + str(Gizmod.getVersion())
print "Dispatcher Initialized from Python: " + str(Dispatcher.getInitialized())

