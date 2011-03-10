#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(osgintrospection, [2.11.1], [http://github.com/sat-metalab/osgintrospection/issues], [osgintrospection], [http://github.com/sat-metalab/osginstrospection])
#[http://www.openscenegraph.org/projects/osg/wiki/GenWrapper])
AC_MSG_NOTICE([Configuring OSG introspection and genwrapper])
AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST # fills $host variable

# Define these substitions here to keep all version information in one place.
# For information on how to properly maintain the library version information,
# refer to the libtool manual, section "Updating library version information":
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
# see http://sourceware.org/autobook/autobook/autobook_91.html
# format is [current:revision:age]
# libtool versioning is different than the project's versioning. It's for the ABI and API.
# It's in the form "current:revision:age" where:
#  * current: Increment when the interface changes. (and set revision to 0)
#  * revision: Increment when the implementation changes, but not the interface.
#  * age: Backward-compatible with how many interface numbers.
AC_SUBST([OSGINTROSPECTION_SO_VERSION], [0:0:0])

# The version of the API. Should be major.minor and not change until not backward-compatible
AC_SUBST([OSGINTROSPECTION_API_VERSION], [2.11])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
    then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
# AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([doxyfile])])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for libraries
AC_CHECK_LIB([m],[sqrt])
PKG_CHECK_MODULES(XML, libxml-2.0 >= 2.0)
PKG_CHECK_MODULES([LIBXML2], libxml-2.0 >= 2.0)

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

#TODO: check for boost::spirit

# Check for OpenSceneGraph:
#PKG_CHECK_MODULES(OpenSceneGraph, openscenegraph >= 2.8.0, , AC_MSG_ERROR([missing OpenSceneGraph]))
# AC_CHECK_LIB(osg, osgGetVersion, , AC_MSG_ERROR([missing OpenSceneGraph]),)

# and osgIntrospection:
# AC_CHECK_LIB(osgIntrospection, osgIntrospectionGetVersion, OSGINTROSPECTION_LIB="-losgIntrospection", AC_MSG_ERROR([missing OpenSceneGraph Introspection library]),)
# AC_SUBST([OSGINTROSPECTION_LIB])

# another way to check for OSG libs?:
#AC_CHECK_LIB(osg,osgGetVersion)

# AC_CHECK_LIB(OpenThreads,OpenThreadsGetVersion)

PKG_CHECK_MODULES(OPENTHREADS, openthreads >= 2.5.0, , AC_MSG_ERROR([missing OpenThreads]))

# Mac OS X specific configure options
#AC_ARG_WITH(osg_framework, [ --with-osg-framework=PREFIX Specify the prefix path to osg frameworks [default=standard framework paths]])
#AC_CHECK_FRAMEWORK(osg, [#include <osg/Version>])
#AC_CHECK_FRAMEWORK(OpenThreads, [#include <OpenThreads/Version>])

# GNU help2man creates man pages from --help output; in many cases, this
# is sufficient, and obviates the need to maintain man pages separately.
# However, this means invoking executables, which we generally cannot do
# when cross-compiling, so we test to avoid that (the variable
# "cross_compiling" is set by AC_PROG_CC).
if test $cross_compiling = no; then
    AM_MISSING_PROG(HELP2MAN, help2man)
else
    HELP2MAN=:
fi

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
  # OSX does not include /usr/local/lib/pkgconfig path, so we export it here
  # (for everyone, just in case)
  # PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
  # export PKG_CONFIG_PATH
  # LDFLAGS="$LDFLAGS -L/usr/local/lib -L/usr/local/lib64"
esac

CXXFLAGS+=" -Wfatal-errors"
# CXXFLAGS+=" -Wall -Wextra -Wfatal-errors -Werror -Wnon-virtual-dtor "

AC_CONFIG_FILES([
        Makefile
        osgintrospection.pc 
        src/Makefile
        doxyfile 
        src/genwrapper/Makefile
        src/osgIntrospection/Makefile
        osgintrospection-${OSGINTROSPECTION_API_VERSION}.pc:osgintrospection.pc.in
    ])

AC_OUTPUT
