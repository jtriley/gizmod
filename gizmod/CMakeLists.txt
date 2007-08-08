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
