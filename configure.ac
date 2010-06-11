#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(genwrapper, [1.2.1], [http://www.openscenegraph.org/projects/osg/wiki/GenWrapper])
AC_MSG_NOTICE([Configuring OSG genwrapper])
AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])
#AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST # fills $host variable

# Special cases
case "$host" in *-darwin* | *-macos10*)
  if test -d /opt/local ; then
    CPPFLAGS="$CPPFLAGS -I/opt/local/include"
    LDFLAGS="$LDFLAGS -L/opt/local/lib"
  elif test -d /sw ; then
    CPPFLAGS="$CPPFLAGS -I/sw/include"
    LDFLAGS="$LDFLAGS -L/sw/lib"
  fi
  ;;
esac

# OSX does not include /usr/local/lib/pkgconfig path, so we export it here
# (for everyone, just in case)
PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
export PKG_CONFIG_PATH

CXXFLAGS+=" -Wfatal-errors"
LDFLAGS="$LDFLAGS -L/usr/local/lib -L/usr/local/lib64"

AC_CONFIG_FILES([
        Makefile 
        src/Makefile])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for libraries
AC_CHECK_LIB([m],[sqrt])
PKG_CHECK_MODULES(XML, libxml-2.0 >= 2.0)
PKG_CHECK_MODULES([LIBXML2], libxml-2.0 >= 2.0)
#AC_SUBST(LIBXML_LIBS)
#AC_SUBST(LIBXML_CFLAGS)

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h stddef.h stdlib.h string.h sys/time.h])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([gettimeofday memmove mkdir setenv sqrt strchr strpbrk uname])

# Check for boost:
AX_BOOST_BASE([1.35])

AX_BOOST_REGEX
if test "x${ax_cv_boost_regex}" = "xno" ; then
    AC_MSG_ERROR([missing package: libboost-regex-dev])
fi

AX_BOOST_FILESYSTEM
if test "x${ax_cv_boost_filesystem}" = "xno" ; then
        AC_MSG_ERROR([missing package: libboost-filesystem-dev])
fi

AX_BOOST_THREAD
if test "x${ax_cv_boost_thread}" = "xno" ; then
    AC_MSG_ERROR([missing package: libboost-thread-dev])
fi

# Check for OpenSceneGraph:
#PKG_CHECK_MODULES(OpenSceneGraph, openscenegraph >= 2.8.0, , AC_MSG_ERROR([missing OpenSceneGraph]))
AC_CHECK_LIB(osg, osgGetVersion, , AC_MSG_ERROR([missing OpenSceneGraph]),)

# and osgIntrospection:
AC_CHECK_LIB(osgIntrospection, osgIntrospectionGetVersion, OSGINTROSPECTION_LIB="-losgIntrospection", AC_MSG_ERROR([missing OpenSceneGraph Introspection library]),)
AC_SUBST([OSGINTROSPECTION_LIB])

# another way to check for OSG libs?:
#AC_CHECK_LIB(osg,osgGetVersion)
#AC_CHECK_LIB(OpenThreads,OpenThreadsGetVersion)


# Mac OS X specific configure options
#AC_ARG_WITH(osg_framework, [ --with-osg-framework=PREFIX Specify the prefix path to osg frameworks [default=standard framework paths]])
#AC_CHECK_FRAMEWORK(osg, [#include <osg/Version>])
#AC_CHECK_FRAMEWORK(OpenThreads, [#include <OpenThreads/Version>])

#AC_OUTPUT(Makefile src/Makefile)
AC_OUTPUT
