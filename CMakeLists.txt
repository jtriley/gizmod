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

project(Gizmod)

cmake_minimum_required(VERSION 2.6)

#################################
# Defines
##############

# global needed variables
set(APPLICATION_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "4")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(APPLICATION_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")

#################################
# Preamble
##############

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ 
# is checked
set(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake/Modules
)

# set default build type to release
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)

# add definitions
include(DefineProjectDefaults)
include(DefineProjectOptions)
include(DefineCompilerFlags)
include(DefineInstallationPaths)

# add macros
include(MacroAddPlugin)
include(MacroEnsureOutOfSourceBuild)
include(ConfigureChecks.cmake)

# config.h
configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

#################################
# Sub-directories
##############

subdirs(libH libGizmod gizmod scripts visplugin)

#################################
# Information
##############

message(STATUS "Installation Variables:
   Build Type       (CMAKE_BUILD_TYPE):     ${CMAKE_BUILD_TYPE}
   Install Prefix   (CMAKE_INSTALL_PREFIX): ${CMAKE_INSTALL_PREFIX}
   Data Dir         (DATA_INSTALL_DIR):     ${DATA_INSTALL_DIR}
   Lib Dir          (LIB_INSTALL_DIR):      ${LIB_INSTALL_DIR}
   Plugin Dir       (PLUGIN_INSTALL_DIR):   ${PLUGIN_INSTALL_DIR}
   Config Dir       (SYSCONF_INSTALL_DIR):  ${SYSCONF_INSTALL_DIR}
   Build vis plugin (BUILD_VIS_PLUGIN):     ${BUILD_VIS_PLUGIN}"
)

#################################
# Packing
##############

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Gizmo Daemon")
set(CPACK_PACKAGE_VENDOR "Gizmod")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_FILE_NAME "gizmod-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-linux-i686")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "gizmod-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
set(CPACK_GENERATOR "TGZ;TBZ2;ZIP")
set(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")
set(CPACK_SOURCE_IGNORE_FILES "\\\\.svn/;/debug/;/optimized/;/documentation/;Doxyfile;[a-z]*\\\\.kdev*;[a-z]*\\\\.tag;[a-z]*\\\\.pyc")
if (WIN32 AND NOT UNIX)
	# There is a bug in NSI that does not handle full unix paths properly. Make
	# sure there is at least one set of four (4) backlasshes.
	SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
	SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
	SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
	SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
	SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
	SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
	SET(CPACK_NSIS_MODIFY_PATH ON)
else (WIN32 AND NOT UNIX)
	set(CPACK_STRIP_FILES "gizmod/gizmod")
	set(CPACK_SOURCE_STRIP_FILES "")
endif (WIN32 AND NOT UNIX)
set(CPACK_PACKAGE_EXECUTABLES "gizmod" "gizmod")
include(CPack)
