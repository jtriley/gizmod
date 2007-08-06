#################################
# Project
##############

project(libGizmod)

#################################
# Dependencies
##############

find_package(Boost REQUIRED QUIET)
find_package(PythonLibs REQUIRED)
find_package(Alsa REQUIRED)
find_package(X11 REQUIRED)

#ALSA_CONFIGURE_FILE(${CMAKE_BINARY_DIR}/config-alsa.h)

#################################
# Compiler Switches
##############

include_directories(
	${includes} 
	${CMAKE_BINARY_DIR}
	${Boost_INCLUDE_DIRS} 
	${X11_INCLUDE_DIR}
	${ALSA_INCLUDES}
	${PYTHON_INCLUDE_PATH}
)

#################################
# Source Files
##############

add_library(Gizmod SHARED
	Alsa.cpp
	AlsaEvent.cpp
	AlsaInterface.cpp
	AlsaMixer.cpp
	AlsaMixerElements.cpp
	AlsaMixerInterface.cpp
	AlsaSoundCard.cpp
	AlsaSoundCardInterface.cpp
	CPUUsage.cpp
	Gizmo.cpp
	GizmoATIX10.cpp
	GizmoClient.cpp
	GizmoEvent.cpp
	GizmoEventATIX10.cpp
	GizmoEventCPUUsage.cpp
	GizmoEventLIRC.cpp
	GizmoEventPowermate.cpp
	GizmoEventSoundCard.cpp
	GizmoEventSoundVisualization.cpp
	GizmoEventStandard.cpp
	GizmoEventWindowFocus.cpp
	GizmoLIRC.cpp
	GizmoLinuxInputDevice.cpp
	GizmoLinuxInputEvent.cpp
	GizmoPowermate.cpp
	GizmoStandard.cpp
	GizmodShared.cpp
	GizmodThread.cpp
	GizmodTimer.cpp
	Processes.cpp
	X11FocusWatcher.cpp
)

#################################
# Linking
##############

link_directories(
	${GIZMOD_BINARY_DIR}/libH
)

target_link_libraries(Gizmod
	H
	boost_filesystem 
	boost_thread 
	boost_serialization 
	boost_python
	${PYTHON_LIBRARIES}
	${ASOUND_LIBRARY}
	${X11_LIBRARIES}
)

#################################
# Install Files
##############

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
install(
	FILES
		${headers}
	DESTINATION
		include/gizmod
)

install(TARGETS Gizmod
	LIBRARY DESTINATION lib
)
