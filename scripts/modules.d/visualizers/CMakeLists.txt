#################################
# Install Files
##############

file(GLOB scripts "${CMAKE_CURRENT_SOURCE_DIR}/*.py")

install(
	FILES
		${scripts}
	DESTINATION
		${SYSCONF_INSTALL_DIR}/gizmod/modules.d/visualizers
)
