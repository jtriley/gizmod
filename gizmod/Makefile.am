bin_PROGRAMS = gizmod
#gizmod_includedir = $(includedir)/gizmod
#gizmod_include_HEADERS = Main.hpp GizmoDaemon.hpp GizmodEventHandlerInterface.hpp GizmoUtils.hpp GizmoKeyDefPythonExposures.hpp 
gizmod_SOURCES =         Main.cpp GizmoDaemon.cpp GizmodEventHandlerInterface.cpp GizmoUtils.cpp
gizmod_LDADD = ../libH/libH.la ../libGizmod/libGizmod.la $(BOOST_LDFLAGS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_PYTHON_LIB) ${BOOST_SERIALIZATION_LIB} ${X11_LIBS} ${ALSA_LIBS}
