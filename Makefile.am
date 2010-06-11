# "foreign" means not GNU, and is common for avoiding boring messages about files organized differently from what gnu expects

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

man_MANS = genwrapper.1 
EXTRA_DIST = $(man_MANS) README LICENSE
MAINTAINERCLEANFILES = $(man_MANS)

# The man pages depend on the --help strings and the version number.
common_mandeps = $(top_srcdir)/configure.ac

# Depend on the source, not the binary; we don't need to regenerate the
# binary when any source file changes, only the main one.
# Use -o so that the `missing' program can infer the output file.
genwrapper.1: $(top_srcdir)/src/main.cpp $(top_srcdir)/man-genwrapper.txt
	$(HELP2MAN) --include=man-genwrapper.txt --name="OpenSceneGraph Introspection Wrapper Generator" --no-info $(top_builddir)/src/genwrapper -o $@
