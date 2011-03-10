#AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CXXFLAGS = -I$(top_srcdir)/include $(OPENTHREADS_CFLAGS)
AM_LIBS = $(OPENTHREADS_LIBS)

# use lib_LTLIBRARIES to build a shared lib:
lib_LTLIBRARIES = libosgintrospection-@OSGINTROSPECTION_API_VERSION@.la

## Define the source file list for the "libosgintrospection-@OSGINTROSPECTION_API_VERSION@.la"
## target.  Note that @OSGINTROSPECTION_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## The file extension .cc is recognized by Automake, and makes it produce
## rules which invoke the C++ compiler to produce a libtool object file (.lo)
## from each source file.  Note that it is not necessary to list header files
## which are already listed elsewhere in a _HEADERS variable assignment.

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libosgintrospection_@OSGINTROSPECTION_API_VERSION@_la_SOURCES = \
    ConstructorInfo.cpp \
    CustomAttributeProvider.cpp \
    DefaultReflectors.cpp \
    MethodInfo.cpp \
    PropertyInfo.cpp \
    Reflection.cpp \
    Reflector.cpp \
    Type.cpp \
    Utility.cpp \
    Value.cpp \
    Version.cpp

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libosgintrospection_@OSGINTROSPECTION_API_VERSION@_la_LDFLAGS = $(OPENTHREADS_LIBS) -export-dynamic -version-info $(OSGINTROSPECTION_SO_VERSION)

libosgintrospection_@OSGINTROSPECTION_API_VERSION@_la_includedir = $(includedir)/osgIntrospection-$(OSGINTROSPECTION_SO_VERSION)

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libosgintrospection_@OSGINTROSPECTION_API_VERSION@_la_include_HEADERS = \
    $(top_srcdir)/include/osgIntrospection/Attributes \
    $(top_srcdir)/include/osgIntrospection/Comparator \
    $(top_srcdir)/include/osgIntrospection/ConstructorInfo \
    $(top_srcdir)/include/osgIntrospection/Converter \
    $(top_srcdir)/include/osgIntrospection/ConverterProxy \
    $(top_srcdir)/include/osgIntrospection/CustomAttribute \
    $(top_srcdir)/include/osgIntrospection/CustomAttributeProvider \
    $(top_srcdir)/include/osgIntrospection/Exceptions \
    $(top_srcdir)/include/osgIntrospection/Export \
    $(top_srcdir)/include/osgIntrospection/ExtendedTypeInfo \
    $(top_srcdir)/include/osgIntrospection/InstanceCreator \
    $(top_srcdir)/include/osgIntrospection/MethodInfo \
    $(top_srcdir)/include/osgIntrospection/ParameterInfo \
    $(top_srcdir)/include/osgIntrospection/PropertyInfo \
    $(top_srcdir)/include/osgIntrospection/PublicMemberAccessor \
    $(top_srcdir)/include/osgIntrospection/ReaderWriter \
    $(top_srcdir)/include/osgIntrospection/Reflection \
    $(top_srcdir)/include/osgIntrospection/ReflectionMacros \
    $(top_srcdir)/include/osgIntrospection/Reflector \
    $(top_srcdir)/include/osgIntrospection/StaticMethodInfo \
    $(top_srcdir)/include/osgIntrospection/Type \
    $(top_srcdir)/include/osgIntrospection/TypedConstructorInfo \
    $(top_srcdir)/include/osgIntrospection/TypedMethodInfo \
    $(top_srcdir)/include/osgIntrospection/TypeNameAliasProxy \
    $(top_srcdir)/include/osgIntrospection/type_traits \
    $(top_srcdir)/include/osgIntrospection/Utility \
    $(top_srcdir)/include/osgIntrospection/Value \
    $(top_srcdir)/include/osgIntrospection/variant_cast \
    $(top_srcdir)/include/osgIntrospection/Version

