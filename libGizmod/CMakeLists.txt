############################################################################
##############################################################################
## 
##  Copyright (c) 2007, Tim Burrell
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at 
##
##	http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and 
##  limitations under the License. 
##  
############################################################################
  ############################################################################

#################################
# Project
##############

project(libGizmod)

#################################
# Dependencies
##############

find_package(Boost REQUIRED QUIET)
	if (NOT BOOST_FILESYSTEM_FOUND)
		message(FATAL_ERROR "Boost filesystem was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_FILESYSTEM_FOUND)
	if (NOT BOOST_THREAD-MT_FOUND)
		message(FATAL_ERROR "Boost thread was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_THREAD-MT_FOUND)
	if (NOT BOOST_PYTHON_FOUND)
		message(FATAL_ERROR "Boost python was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_PYTHON_FOUND)
	if (NOT BOOST_SERIALIZATION_FOUND)
		message(FATAL_ERROR "Boost serialization was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_SERIALIZATION_FOUND)
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
	${BOOST_INCLUDE_DIRS} 
	${X11_INCLUDE_DIR}
	${ALSA_INCLUDES}
	${PYTHON_INCLUDE_PATH}
)

add_definitions(
	${BOOST_DEFINITIONS}
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

set_target_properties(Gizmod PROPERTIES VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" SOVERSION "${CPACK_PACKAGE_VERSION_MAJOR}")

#################################
# Linking
##############

link_directories(
	${BOOST_LIBRARY_DIRS}
	${GIZMOD_BINARY_DIR}/libH
)

target_link_libraries(Gizmod
	H
	${BOOST_FILESYSTEM_LIBRARY}
	${BOOST_THREAD_LIBRARY}
	${BOOST_SERIALIZATION_LIBRARY}
	${BOOST_PYTHON_LIBRARY}
	${PYTHON_LIBRARIES}
	${ASOUND_LIBRARY}
	${X11_LIBRARIES}
	${LIBUTIL_LIBRARIES}
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

install(FILES	
		${CMAKE_CURRENT_BINARY_DIR}/libGizmod.so.${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}
		${CMAKE_CURRENT_BINARY_DIR}/libGizmod.so.${CPACK_PACKAGE_VERSION_MAJOR}
		${CMAKE_CURRENT_BINARY_DIR}/libGizmod.so
	DESTINATION 
		lib
)
