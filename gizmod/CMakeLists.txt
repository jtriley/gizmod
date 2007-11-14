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

project(GizmoDaemon)

#################################
# Dependencies
##############

find_package(Boost REQUIRED)
	if (NOT BOOST_PROGRAM_OPTIONS_FOUND)
		message(FATAL_ERROR "Boost program_options was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_PROGRAM_OPTIONS_FOUND)
find_package(PythonLibs REQUIRED)

#################################
# Compiler Switches
##############

include_directories(
	${includes} 
	${CMAKE_BINARY_DIR}
	${BOOST_INCLUDE_DIRS} 
	${PYTHON_INCLUDE_PATH}
)

add_definitions(
	${BOOST_DEFINITIONS}
)

#################################
# Header Files
##############

set(gizmod_HEADERS
	GizmoDaemon.hpp
	GizmoKeyDefPythonExposures.hpp
	GizmoUtils.hpp
	GizmodEventHandlerInterface.hpp
	Main.hpp
)

#################################
# Source Files
##############

add_executable(gizmod
	GizmoDaemon.cpp
	GizmoUtils.cpp
	GizmodEventHandlerInterface.cpp
	Main.cpp
)

#################################
# Linking
##############

link_directories(
	${BOOST_LIBRARY_DIRS}
	${GIZMOD_BINARY_DIR}/libH
	${GIZMOD_BINARY_DIR}/libGizmod
)

target_link_libraries(gizmod
	H
	Gizmod
	${BOOST_PROGRAM_OPTIONS_LIBRARY}
	${PYTHON_LIBRARIES}
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

install(TARGETS gizmod
	RUNTIME DESTINATION bin
)
