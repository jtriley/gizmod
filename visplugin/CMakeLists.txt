############################################################################
##############################################################################
## 
##  Copyright (c) 2007-2008, Tim Burrell
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

project(actor_gizmod)

if(COMMAND cmake_policy)
        cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#################################
# Dependencies
##############

find_package(PythonLibs REQUIRED)
find_package(Boost REQUIRED)
find_package(Libvisual)

#################################

if (LIBVISUAL_FOUND AND BUILD_VIS_PLUGIN)

#################################
# Compiler Switches
##############

include_directories(
	${includes}
	${CMAKE_BINARY_DIR}
	${LIBVISUAL_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
	${PYTHON_INCLUDE_PATH}
)

add_definitions(
	${Boost_DEFINITIONS}
	${LIBVISUAL_DEFINITIONS}
)

#################################
# Source Files
##############

add_library(actor_gizmod SHARED
	GizmodLibVisualCInterface.cpp
	GizmodLibVisualPlugin.cpp
	actor_gizmod.c
)

#################################
# Linking
##############

link_directories(
	${Boost_LIBRARY_DIRS}
	${GIZMOD_BINARY_DIR}/libH
	${GIZMOD_BINARY_DIR}/libGizmod
)

target_link_libraries(actor_gizmod
	H
	Gizmod
	${LIBVISUAL_LIBRARIES}
)

#################################
# Install Files
##############

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
install(
	FILES
		${headers}
	DESTINATION
		include/gizmod/H
)

install(TARGETS actor_gizmod
	LIBRARY DESTINATION ${LIBVISUAL_PLUGINS_DIR}/actor
)

#################################

else (LIBVISUAL_FOUND AND BUILD_VIS_PLUGIN)
	if (BUILD_VIS_PLUGIN)
		message(STATUS "WARNING: libvisual plugin requested, but libvisual NOT FOUND!\n   Not building libvisual plugin!")
	endif (BUILD_VIS_PLUGIN)
endif (LIBVISUAL_FOUND AND BUILD_VIS_PLUGIN)
