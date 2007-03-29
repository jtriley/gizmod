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

##################

CXXFLAGS="$CFLAGS"
CPPFLAGS="$CFLAGS"

##################

echo

AC_CONFIG_FILES([
	Makefile
	libH/Makefile
	gizmod/Makefile
])
AC_OUTPUT

##################

