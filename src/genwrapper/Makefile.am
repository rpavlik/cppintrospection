AM_CXXFLAGS = -I$(top_srcdir)/include
LDADD = $(top_builddir)/src/osgIntrospection/libosgintrospection-@OSGINTROSPECTION_API_VERSION@.la

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = genwrapper

genwrapper_SOURCES = \
    Configuration.cpp \
    Configuration.h \
    FileSystemUtils.cpp \
    FileSystemUtils.h \
    NodeMap.cpp \
    NodeMap.h \
    Notify.cpp \
    Notify.h \
    PathNameUtils.cpp \
    PathNameUtils.h \
    RegistryBuilder.cpp \
    RegistryBuilder.h \
    TypeDesc.cpp \
    TypeDesc.h \
    TypeNameUtils.cpp \
    TypeNameUtils.h \
    TypeRegistry.cpp \
    TypeRegistry.h \
    WrapperGenerator.cpp \
    WrapperGenerator.h \
    XML_node.h \
    main.cpp \
    XML_parser.h

genwrapper_CPPFLAGS = $(XML_CFLAGS) $(BOOST_CPPFLAGS)
genwrapper_LDFLAGS = $(XML_LIBS) $(BOOST_LDFLAGS) $(BOOST_REGEX_LIB)

