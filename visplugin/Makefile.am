if BUILD_PLUGIN_VISPLUGIN

#visplugin_LTLIBRARIES = $(PROJECTM)
#LIBS = -L. -L$(prefix)/lib  @LIBVISUAL_LIBS@
#INCLUDES = $(all_includes) -I$(top_srcdir) -I/usr/include

AM_CFLAGS = @LIBVISUAL_CFLAGS@ -DLINUX
visplugin_LTLIBRARIES = actor_gizmod.la
visplugindir = @LIBVISUAL_PLUGINS_BASE_DIR@/actor
actor_gizmod_la_LIBADD = ../libH/libH.la ${LIBVISUAL_LIBS}
actor_gizmod_la_LDFLAGS = -module -avoid-version  
actor_gizmod_la_SOURCES = actor_gizmod.c GizmodLibVisualCInterface.h GizmodLibVisualCInterface.cpp GizmodLibVisualPlugin.cpp

endif
