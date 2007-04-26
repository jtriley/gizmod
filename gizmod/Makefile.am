bin_PROGRAMS = gizmod
gizmod_includedir = $(includedir)/gizmod
gizmod_include_HEADERS = Main.hpp GizmoDaemon.hpp GizmodEventHandlerInterface.hpp Gizmo.hpp GizmoPowermate.hpp GizmoCPU.hpp GizmoStandard.hpp GizmoEvent.hpp GizmoEventPowermate.hpp GizmoEventCPU.hpp GizmoEventStandard.hpp GizmoLinuxInputDevice.hpp GizmoLinuxInputEvent.hpp X11FocusWatcher.hpp GizmoEventWindowFocus.hpp GizmoLIRC.hpp GizmoEventLIRC.hpp GizmoSoundCard.hpp GizmoEventSoundCard.hpp
gizmod_SOURCES = Main.cpp GizmoDaemon.cpp GizmodEventHandlerInterface.cpp Gizmo.cpp GizmoPowermate.cpp GizmoCPU.cpp GizmoStandard.cpp GizmoEvent.cpp GizmoEventPowermate.cpp GizmoEventCPU.cpp GizmoEventStandard.cpp GizmoLinuxInputDevice.cpp GizmoLinuxInputEvent.cpp X11FocusWatcher.cpp GizmoEventWindowFocus.cpp GizmoLIRC.cpp GizmoEventLIRC.cpp GizmoSoundCard.cpp GizmoEventSoundCard.cpp
gizmod_LDADD = ../libH/libH.la $(BOOST_LDFLAGS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_PYTHON_LIB) ${X11_LIBS}
