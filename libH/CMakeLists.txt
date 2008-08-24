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

project(libH)

if(COMMAND cmake_policy)
        cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#################################
# Dependencies
##############

find_package(Boost REQUIRED)
	if (NOT BOOST_FILESYSTEM_FOUND)
		message(FATAL_ERROR "Boost filesystem was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_FILESYSTEM_FOUND)
	if (NOT BOOST_THREAD-MT_FOUND)
		message(FATAL_ERROR "Boost thread was not found!\nPlease check your boost development library installation.")
	endif (NOT BOOST_THREAD-MT_FOUND)

#################################
# Compiler Switches
##############

include_directories(
	${includes} 
	${CMAKE_BINARY_DIR}
	${BOOST_INCLUDE_DIRS}
)

add_definitions(
	${BOOST_DEFINITIONS}
)

#################################
# Source Files
##############

add_library(H STATIC
	Average.cpp
	Debug.cpp
	Exception.cpp
	FileEventWatcher.cpp
	SignalHandler.cpp
	Socket.cpp
	SocketClient.cpp
	SocketEventWatcher.cpp
	SocketException.cpp
	SocketInterface.cpp
	SocketServer.cpp
	Util.cpp
	UtilFile.cpp
	UtilMath.cpp
	UtilTime.cpp
	stringconverter.cpp
)

#################################
# Linking
##############

link_directories(
	${BOOST_LIBRARY_DIRS}
)

target_link_libraries(H 
	${BOOST_FILESYSTEM_LIBRARY}
	${BOOST_THREAD_LIBRARY}
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
