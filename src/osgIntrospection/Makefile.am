#AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CXXFLAGS = -I$(top_srcdir)/include $(LIBLO_CFLAGS) $(PTHREAD_CFLAGS)
AM_LIBS = $(PTHREAD_LIBS)

# use lib_LTLIBRARIES to build a shared lib:
lib_LTLIBRARIES = libspatosc-@SPATOSC_API_VERSION@.la

## Define the source file list for the "libspatosc-@SPATOSC_API_VERSION@.la"
## target.  Note that @SPATOSC_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## The file extension .cc is recognized by Automake, and makes it produce
## rules which invoke the C++ compiler to produce a libtool object file (.lo)
## from each source file.  Note that it is not necessary to list header files
## which are already listed elsewhere in a _HEADERS variable assignment.

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libspatosc_@SPATOSC_API_VERSION@_la_SOURCES = \
    connection.cpp \
    dmitri_translator.cpp \
    fudi_sender.cpp \
    fudi_translator.cpp \
    geotransform.cpp \
    listener.cpp \
    maths.cpp \
    node.cpp \
    osc_scene.cpp \
    oscreceiver.cpp \
    oscsender.cpp \
    oscutils.cpp \
    scene.cpp \
    soundsource.cpp \
    spatdif_receiver.cpp \
    spatdif_translator.cpp \
    translator.cpp \
    wrapper.cpp

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libspatosc_@SPATOSC_API_VERSION@_la_LDFLAGS = $(LIBLO_LIBS) -export-dynamic -version-info $(SPATOSC_SO_VERSION)

libspatosc_@SPATOSC_API_VERSION@_la_includedir = $(includedir)/spatosc-$(SPATOSC_API_VERSION)/spatosc

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libspatosc_@SPATOSC_API_VERSION@_la_include_HEADERS = \
    $(top_srcdir)/include/connection.h \
    $(top_srcdir)/include/dmitri_translator.h \
    $(top_srcdir)/include/fudi_sender.h \
    $(top_srcdir)/include/fudi_translator.h \
    $(top_srcdir)/include/geotransform.h \
    $(top_srcdir)/include/listener.h \
    $(top_srcdir)/include/maths.h \
    $(top_srcdir)/include/memory.h \
    $(top_srcdir)/include/node.h \
    $(top_srcdir)/include/osc_scene.h \
    $(top_srcdir)/include/oscreceiver.h \
    $(top_srcdir)/include/oscsender.h \
    $(top_srcdir)/include/oscutils.h \
    $(top_srcdir)/include/properties.h \
    $(top_srcdir)/include/property.h \
    $(top_srcdir)/include/scene.h \
    $(top_srcdir)/include/soundsource.h \
    $(top_srcdir)/include/spatdif_receiver.h \
    $(top_srcdir)/include/spatdif_translator.h \
    $(top_srcdir)/include/spatosc.h \
    $(top_srcdir)/include/translator.h \
    $(top_srcdir)/include/unused.h \
    $(top_srcdir)/include/version.h \
    $(top_srcdir)/include/wrapper.h

EXTRA_DIST=$(top_srcdir)/include/config.h $(top_srcdir)/include/vectors.h

