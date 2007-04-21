###########################################################################
##
## gizmod autoconf script
##

AC_INIT([gizmod], [3:0],
        [Tim Burrell <tim.burrell@gmail.com>],
	[gizmod])
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AX_BOOST_BASE([1.33.1])

###########################################################################
##
## Additional Defines
##

test "x$prefix" = x. || test "x$prefix" = xNONE && prefix=/usr/local
AC_DEFINE_UNQUOTED([PACKAGE_PREFIX], ["${prefix}"], [Package Prefix (--prefix)])

AC_DEFINE_UNQUOTED([PACKAGE_SYSCONFDIR], ["$sysconfdir"], [system configuration directory] )
AC_DEFINE([PACKAGE_WHIMSICAL_NAME], ["Harness the blue"], [Package Pet Name / Dedication])

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

AX_BOOST([1.33.1])
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
BOOST_PYTHON_LIB="-l$PYTHON_LIB -lboost_python"
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


##################

CXXFLAGS="$CFLAGS"
CPPFLAGS="$CFLAGS"

##################

echo

AC_CONFIG_FILES([
	Makefile
	libH/Makefile
	gizmod/Makefile
	scripts/Makefile
])
AC_OUTPUT

##################

