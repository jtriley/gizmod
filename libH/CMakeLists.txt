#################################
# Project
##############

project(libH)

#################################
# Dependencies
##############

find_package(Boost REQUIRED QUIET)

#################################
# Compiler Switches
##############

include_directories(
	${includes} 
	${CMAKE_BINARY_DIR}
	${Boost_INCLUDE_DIRS}
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

target_link_libraries(H 
	boost_filesystem 
	boost_thread
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
