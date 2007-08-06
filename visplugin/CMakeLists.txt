#################################
# Project
##############

project(actor_gizmod)

#################################
# Dependencies
##############

find_package(Boost REQUIRED QUIET)
find_package(PythonLibs REQUIRED)
find_package(Libvisual)

#################################

if (NOT LIBVISUAL_FOUND)
      message(STATUS "NOT building libvisual plugin!")
else (NOT LIBVISUAL_FOUND)
      message(STATUS "Building libvisual plugin")

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

endif (NOT LIBVISUAL_FOUND)
