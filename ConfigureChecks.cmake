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
# Includes
##############

INCLUDE(CheckIncludeFile)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckLibraryExists)
INCLUDE(CheckTypeSize)
INCLUDE(CheckCXXSourceCompiles)

#################################
# Defines
##############

SET(PACKAGE ${APPLICATION_NAME})
SET(VERSION ${APPLICATION_VERSION})
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(DATADIR ${DATA_INSTALL_DIR})
SET(LIBDIR ${LIB_INSTALL_DIR})
SET(PLUGINDIR ${PLUGIN_INSTALL_DIR})
SET(SYSCONFDIR ${SYSCONF_INSTALL_DIR})

#################################
# Build libvisual plugin?
##############

# set default build type to release
if (NOT BUILD_VIS_PLUGIN)
	set(BUILD_VIS_PLUGIN False CACHE BOOLEAN FALSE FORCE)
endif (NOT BUILD_VIS_PLUGIN)

#################################
# Boost
##############

find_package(Boost REQUIRED)

#################################
# Inotify
##############

check_include_file(sys/inotify.h	HAVE_INOTIFY_H)		# inotify
if (NOT HAVE_INOTIFY_H)
	message(FATAL_ERROR "You must have sys/inotify.h!")
endif (NOT HAVE_INOTIFY_H)

check_function_exists(inotify_init	HAVE_INOTIFY_INIT)	# inotify
if (NOT HAVE_INOTIFY_INIT)
	message(FATAL_ERROR "You must have inotify_init!")
endif (NOT HAVE_INOTIFY_INIT)

#################################
# Evdev
##############

check_include_file(linux/input.h	HAVE_INPUT_H)		# evdev
if (NOT HAVE_INPUT_H)
	message(FATAL_ERROR "You must have linux/input.h!")
endif (NOT HAVE_INPUT_H)

#################################
# openpty / forkpty
##############

#set(CMAKE_REQUIRED_LIBRARIES util) 
check_function_exists(openpty		HAVE_OPENPTY)		# openpty
if (NOT HAVE_OPENPTY)
	check_library_exists(util openpty "" HAVE_LIBUTIL)
	if (HAVE_LIBUTIL)
		set(HAVE_OPENPTY True)
		set(LIBUTIL_LIBRARIES "util")
	else (HAVE_LIBUTIL)
		message(FATAL_ERROR "You must have openpty in libutil!")
	endif (HAVE_LIBUTIL)
endif (NOT HAVE_OPENPTY)
