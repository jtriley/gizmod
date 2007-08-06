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
