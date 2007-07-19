###########################################################################
##
## gizmod autoconf script
##

AC_INIT([gizmod], [3:4],
        [Tim Burrell <tim.burrell@gmail.com>],
	[gizmod])
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AX_BOOST_BASE([1.34])

###########################################################################
##
## Additional Defines
##

test "x$prefix" = x. || test "x$prefix" = xNONE && prefix=/usr/local
AC_DEFINE_UNQUOTED([PACKAGE_PREFIX], ["${prefix}"], [Package Prefix (--prefix)])
AC_DEFINE_UNQUOTED([PACKAGE_SYSCONFDIR], ["$sysconfdir"], [system configuration directory] )
AC_DEFINE([PACKAGE_WHIMSICAL_NAME], ["Inputron"], [Package Pet Name / Dedication])

#########

AC_CONFIG_HEADERS(config.h)

#############################################################################
##
## Check for inotify support (kernel >= 2.6.13)
##

AC_CHECK_HEADER(sys/inotify.h, [
	AC_DEFINE(HAVE_INOTIFY_H, 1, [Has sys/inotify.h])
	], [
	AC_MSG_ERROR([Cannot find sys/inotify.h! -- You must have Linux kernel >= 2.6.13])
	])
	
AC_CHECK_FUNC(inotify_init, [
	AC_DEFINE(HAVE_INOTIFY_INIT, 1, [Has inotify_init])
	], [
	AC_MSG_ERROR([Cannot use inotify_init! -- You must have Linux kernel >= 2.6.13])
	])

#############################################################################
##
## Check for Boost
##

AX_BOOST([1.34])
CFLAGS="$CFLAGS -fexceptions"
if test "$with_boost" != "yes" ; then
	AC_MSG_ERROR([You must install / configure with Boost (--with-boost)])
fi
CFLAGS="$CFLAGS $BOOST_CFLAGS"

#############################################################################
##
## Check for Boost.Python
##

AX_BOOST_PYTHON
CFLAGS="$CFLAGS -I$PYTHON_INCLUDE_DIR"
BOOST_PYTHON_LIB="-l$PYTHON_LIB -l$BOOST_PYTHON_LIB"
AC_SUBST(BOOST_PYTHON_LIB)

#############################################################################
##
## Check for X11
##

AC_MSG_CHECKING(X11 location)
AC_ARG_WITH(X11-prefix,
              [  --with-X11-prefix       set installation path of X11])

if test "$with_X11_prefix" ; then
	AC_MSG_RESULT($with_X11_prefix)
else
	with_X11_prefix="/usr/X11R6/"
	AC_MSG_RESULT(Not Specified.  Using $with_X11_prefix)
fi

X11_LIBS="-L$with_X11_prefix/lib -L$with_X11_prefix/lib64 -lX11"
TEMPLDFLAGS="${LDFLAGS}"
LDFLAGS="${LDFLAGS} ${X11_LIBS}"
AC_CHECK_LIB(X11, XOpenDisplay, [
	AC_DEFINE(HAVE_X11LIB, 1, [Use -lX11])
	], [
	AC_MSG_ERROR([Cannot find lib X11!])
	])
		
AC_CHECK_HEADER(X11/Xlib.h, [
	AC_DEFINE(HAVE_X11_XLIB_H, 1, [Has X11/Xlib.h])
	], [
	AC_MSG_ERROR([Cannot find X11/Xlib.h!])
	])
	
AC_CHECK_HEADER(X11/Xutil.h, [
	AC_DEFINE(HAVE_X11_XUTIL_H, 1, [Has X11/Xutil.h])
	], [
	AC_MSG_ERROR([Cannot find X11/Xutil.h!])
	])

AC_CHECK_HEADER(X11/keysym.h, [
	AC_DEFINE(HAVE_X11_KEYSYM_H, 1, [Has X11/keysym.h])
	], [
	AC_MSG_ERROR([Cannot find X11/keysym.h!])
	])

AC_CHECK_HEADER(X11/Xatom.h, [
	AC_DEFINE(HAVE_X11_XATOM_H, 1, [Has X11/Xatom.h])
	], [
	AC_MSG_ERROR([Cannot find X11/Xatom.h!])
	])

LDFLAGS="${TEMPLDFLAGS}"
AC_SUBST(X11_LIBS)

#############################################################################
##
## Check for Alsa
##

ALSA_LIBS=""

AC_CHECK_LIB(asound, snd_mixer_open, [
	AC_DEFINE(HAVE_ASOUND, 1, [Use -lasound])
	ALSA_LIBS="-lasound"
	], AC_MSG_ERROR([You must have ALSA Installed!])
	)

AC_CHECK_HEADER(alsa/asoundlib.h, [
	AC_DEFINE(HAVE_ASOUNDLIB_H, 1, [Has alsa/asoundlib.h])
	], [
	AC_MSG_ERROR([You must have the ALSA development headers installed!])
	])
	
AC_SUBST(ALSA_LIBS)

#########################################################################
##
## Check whether to build libVisual plugin
##

##################
## enabled?
########

AC_MSG_CHECKING(Whether or not to build libVisual plugin)
AC_ARG_ENABLE(visplugin,
              [  --enable-visplugin      build libVisual plugin               <default = no>],
              [enable_visplugin="$enableval"], enable_visplugin=no)
AC_MSG_RESULT($enable_visplugin)

AM_CONDITIONAL(BUILD_PLUGIN_VISPLUGIN, test x$enable_visplugin = xyes)

##################
## can we build it if it's enabled?
########

if test "$enable_visplugin" == "yes"; then

# check for libvisual
LIBVISUAL_CFLAGS=""
LIBVISUAL_LIBS=""
PKG_CHECK_MODULES(LIBVISUAL, libvisual-0.4 >= 0.4.0, [libvis="yes"], [libvis="no"])
if test x$libvis = xno; then
	AC_MSG_ERROR([*** libvisual not found.
			libvisual is needed to build this package.
			You can download libvisual at http://libvisual.sf.net/])
fi
AC_SUBST(LIBVISUAL_LIBS)
AC_SUBST(LIBVISUAL_CFLAGS)

# check for install dir
AC_ARG_WITH([plugins_base_dir],
            AC_HELP_STRING([--with-plugins_base_dir="dir"],
                           [Install plugins to this base directory. Defaults to Libvisual's base dir ]),
dnl ' # fix string coloring ;)
	    [plugins_base_dir=$withval],
	    [plugins_base_dir=])

AC_MSG_CHECKING([where to install plugins])

if test -z "$plugins_base_dir"; then
    plugins_base_dir=`$PKG_CONFIG --variable=pluginsbasedir libvisual-0.4`
    AC_MSG_RESULT([$plugins_base_dir])
else
    if test -d "$plugins_base_dir"; then
        AC_MSG_RESULT([$plugins_base_dir])
    else
        AC_MSG_RESULT([not found])
        AC_MSG_ERROR([Specified plugins base directory "$plugins_base_dir" is not accesible!])
        exit 1
    fi
fi

LIBVISUAL_PLUGINS_BASE_DIR="$plugins_base_dir"
AC_SUBST(LIBVISUAL_PLUGINS_BASE_DIR)

fi

##################

CXXFLAGS="$CFLAGS"
CPPFLAGS="$CFLAGS"

##################

echo

AC_CONFIG_FILES([
	Makefile
	libH/Makefile
	libGizmod/Makefile
	gizmod/Makefile
	scripts/Makefile
	scripts/modules.d/Makefile
	scripts/modules.d/bases/Makefile
	scripts/modules.d/visualizers/Makefile
	visplugin/Makefile
])
AC_OUTPUT

##################

echo
echo "Build Parameters:"
echo

if test "$enable_visplugin" == "yes"; then
	echo " libVisual Gizmo LED Visualization Plugin: Enabled"
else
	echo " libVisual Gizmo LED Visualization Plugin: Disabled"
fi

echo
