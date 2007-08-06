# - Try to find the libvisual library
# Once done this will define
#
#  LIBVISUAL_FOUND - system has libvisual
#  LIBVISUAL_INCLUDE_DIR - the libvisual include directory
#  LIBVISUAL_LIBRARIES - Link these to use libvisual
#  LIBVISUAL_DEFINITIONS - Compiler switches required for using libvisual
#  LIBVISUAL_PLUGINS_DIR - libvisual plugins dir
#

set(_visual "visual-0.4")

if(NOT WIN32)
    # use pkg-config to get the directories and then use these values
    # in the FIND_PATH() and FIND_LIBRARY() calls
    INCLUDE(UsePkgConfig)
    INCLUDE(UsePkgConfigVariable)
  
    # get info from pkgconfig
    PKGCONFIG(lib${_visual} _LIBVISUALIncDir _LIBVISUALLinkDir _LIBVISUALLinkFlags _LIBVISUALCflags)
    set(LIBVISUAL_DEFINITIONS ${_LIBVISUALCflags})
    
    # get plugins dir
    PKGCONFIG_VAR(lib${_visual} "pluginsbasedir" _LIBVISUALPluginDir)
    set(LIBVISUAL_PLUGINS_DIR ${_LIBVISUALPluginDir})
endif(NOT WIN32)
FIND_PATH(LIBVISUAL_INCLUDE_DIR libvisual/libvisual.h
    ${_LIBVISUALIncDir}
    /usr/include
    /usr/local/include
)

FIND_LIBRARY(LIBVISUAL_LIBRARIES NAMES ${_visual}
    PATHS
    ${_LIBVISUALLinkDir}
    /usr/lib
    /usr/local/lib
)
  
if (LIBVISUAL_INCLUDE_DIR AND LIBVISUAL_LIBRARIES)
     set(LIBVISUAL_FOUND TRUE)
endif (LIBVISUAL_INCLUDE_DIR AND LIBVISUAL_LIBRARIES)
  
if (NOT LIBVISUAL_FOUND)
    if (Libvisual_FIND_REQUIRED)
      message(FATAL_ERROR "Could NOT find libvisual")
    else (Libvisual_FIND_REQUIRED)
      message(STATUS "Could NOT find libvisual")
    endif (Libvisual_FIND_REQUIRED)
endif (NOT LIBVISUAL_FOUND)
  
MARK_AS_ADVANCED(LIBVISUAL_INCLUDE_DIR LIBVISUAL_LIBRARIES)
