# "foreign" means not GNU, and is common for avoiding boring messages about files organized differently from what gnu expects

ACLOCAL_AMFLAGS = -I m4
MAN_TEXT_FILES=man-genwrapper.txt
SUBDIRS = src

man_MANS = genwrapper.1 
EXTRA_DIST = $(man_MANS) README LICENSE $(MAN_TEXT_FILES)
MAINTAINERCLEANFILES = $(man_MANS)

# The man pages depend on the --help strings and the version number.
common_mandeps = $(top_srcdir)/configure.ac

# Depend on the source, not the binary; we don't need to regenerate the
# binary when any source file changes, only the main one.
# Use -o so that the `missing' program can infer the output file.
genwrapper.1: $(top_srcdir)/src/genwrapper/main.cpp $(top_srcdir)/man-genwrapper.txt
	$(HELP2MAN) --include=man-genwrapper.txt --name="OpenSceneGraph Introspection Wrapper Generator" --no-info $(top_builddir)/src/genwrapper/genwrapper -o $@


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = osgintrospection-@OSGINTROSPECTION_API_VERSION@.pc

dist_noinst_SCRIPTS = autogen.sh

# man pages:
if HAVE_DOXYGEN
dist_man_MANS = $(top_srcdir)/man/man3/*.3
$(top_srcdir)/man/man3/*.3: doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) doxyfile
	echo `date -R` > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_builddir)/man
	rm -rf html
endif 

