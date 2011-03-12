#AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CXXFLAGS = -I$(top_srcdir)/include $(OPENTHREADS_CFLAGS)
AM_LIBS = $(OPENTHREADS_LIBS)

# use lib_LTLIBRARIES to build a shared lib:
lib_LTLIBRARIES = libcppintrospection-@CPPINTROSPECTION_API_VERSION@.la

## Define the source file list for the "libosgintrospection-@CPPINTROSPECTION_API_VERSION@.la"
## target.  Note that @CPPINTROSPECTION_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## The file extension .cc is recognized by Automake, and makes it produce
## rules which invoke the C++ compiler to produce a libtool object file (.lo)
## from each source file.  Note that it is not necessary to list header files
## which are already listed elsewhere in a _HEADERS variable assignment.

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libcppintrospection_@CPPINTROSPECTION_API_VERSION@_la_SOURCES = \
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
libcppintrospection_@CPPINTROSPECTION_API_VERSION@_la_LDFLAGS = $(OPENTHREADS_LIBS) -export-dynamic -version-info $(CPPINTROSPECTION_SO_VERSION)

libcppintrospection_@CPPINTROSPECTION_API_VERSION@_la_includedir = $(includedir)/cppintrospection-$(CPPINTROSPECTION_API_VERSION)/cppintrospection

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libcppintrospection_@CPPINTROSPECTION_API_VERSION@_la_include_HEADERS = \
    $(top_srcdir)/include/cppintrospection/Attributes \
    $(top_srcdir)/include/cppintrospection/Comparator \
    $(top_srcdir)/include/cppintrospection/ConstructorInfo \
    $(top_srcdir)/include/cppintrospection/Converter \
    $(top_srcdir)/include/cppintrospection/ConverterProxy \
    $(top_srcdir)/include/cppintrospection/CustomAttribute \
    $(top_srcdir)/include/cppintrospection/CustomAttributeProvider \
    $(top_srcdir)/include/cppintrospection/Exceptions \
    $(top_srcdir)/include/cppintrospection/Export \
    $(top_srcdir)/include/cppintrospection/ExtendedTypeInfo \
    $(top_srcdir)/include/cppintrospection/InstanceCreator \
    $(top_srcdir)/include/cppintrospection/MethodInfo \
    $(top_srcdir)/include/cppintrospection/ParameterInfo \
    $(top_srcdir)/include/cppintrospection/PropertyInfo \
    $(top_srcdir)/include/cppintrospection/PublicMemberAccessor \
    $(top_srcdir)/include/cppintrospection/ReaderWriter \
    $(top_srcdir)/include/cppintrospection/Reflection \
    $(top_srcdir)/include/cppintrospection/ReflectionMacros \
    $(top_srcdir)/include/cppintrospection/Reflector \
    $(top_srcdir)/include/cppintrospection/StaticMethodInfo \
    $(top_srcdir)/include/cppintrospection/Type \
    $(top_srcdir)/include/cppintrospection/TypedConstructorInfo \
    $(top_srcdir)/include/cppintrospection/TypedMethodInfo \
    $(top_srcdir)/include/cppintrospection/TypeNameAliasProxy \
    $(top_srcdir)/include/cppintrospection/type_traits \
    $(top_srcdir)/include/cppintrospection/Utility \
    $(top_srcdir)/include/cppintrospection/Value \
    $(top_srcdir)/include/cppintrospection/variant_cast \
    $(top_srcdir)/include/cppintrospection/Version

