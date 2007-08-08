#################################
# Project
##############

project(libH)

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
