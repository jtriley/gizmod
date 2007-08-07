#################################
# Project
##############

project(Gizmod)

#################################
# Defines
##############

# global needed variables
set(APPLICATION_NAME ${PROJECT_NAME})
set(APPLICATION_VERSION "3.4")

#################################
# Preamble
##############

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is check$
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
	Build Type     (CMAKE_BUILD_TYPE):     ${CMAKE_BUILD_TYPE}
	Install Prefix (CMAKE_INSTALL_PREFIX): ${CMAKE_INSTALL_PREFIX}
	Data Dir       (DATA_INSTALL_DIR):     ${DATA_INSTALL_DIR}
	Lib Dir        (LIB_INSTALL_DIR):      ${LIB_INSTALL_DIR}
	Plugin Dir     (PLUGIN_INSTALL_DIR):   ${PLUGIN_INSTALL_DIR}
	Config Dir     (SYSCONF_INSTALL_DIR):  ${SYSCONF_INSTALL_DIR}"
)
