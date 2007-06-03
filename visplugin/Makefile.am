if BUILD_PLUGIN_VISPLUGIN

AM_CFLAGS = @LIBVISUAL_CFLAGS@ -DLINUX
visplugin_LTLIBRARIES = actor_gizmod.la
visplugindir = @LIBVISUAL_PLUGINS_BASE_DIR@/actor
actor_gizmod_la_LIBADD = ../libH/libH.la ../libGizmod/libGizmod.la ${LIBVISUAL_LIBS} -l{PYTHON_LIB}
actor_gizmod_la_LDFLAGS = -module -avoid-version  
actor_gizmod_la_SOURCES = actor_gizmod.c GizmodLibVisualCInterface.h GizmodLibVisualCInterface.cpp GizmodLibVisualPlugin.cpp

endif
