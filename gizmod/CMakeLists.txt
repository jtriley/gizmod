#################################
# Project
##############

project(GizmoDaemon)

#################################
# Dependencies
##############

find_package(Boost REQUIRED QUIET)
find_package(PythonLibs REQUIRED)

#################################
# Compiler Switches
##############

include_directories(
	${includes} 
	${CMAKE_BINARY_DIR}
	${Boost_INCLUDE_DIRS} 
	${PYTHON_INCLUDE_PATH}
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
	${GIZMOD_BINARY_DIR}/libH
	${GIZMOD_BINARY_DIR}/libGizmod
)

target_link_libraries(gizmod
	H
	Gizmod
	boost_program_options
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
