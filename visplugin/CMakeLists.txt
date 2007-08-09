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

if (LIBVISUAL_FOUND AND BUILD_VIS_PLUGIN)

#################################
# Compiler Switches
##############

include_directories(
	${includes} 
	${CMAKE_BINARY_DIR}
	${LIBVISUAL_INCLUDE_DIR}
	${BOOST_INCLUDE_DIRS}
	${PYTHON_INCLUDE_PATH}
)

add_definitions(
	${BOOST_DEFINITIONS}
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
	${BOOST_LIBRARY_DIRS}
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