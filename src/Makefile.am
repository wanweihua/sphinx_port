SRC_SPHINX = sphinx.cpp sphinxexcerpt.cpp sphinxquery.cpp \
	sphinxsoundex.cpp sphinxmetaphone.cpp sphinxstemen.cpp sphinxstemru.cpp sphinxstemcz.cpp sphinxstemar.cpp \
	sphinxutils.cpp sphinxstd.cpp sphinxsort.cpp sphinxexpr.cpp sphinxfilter.cpp \
	sphinxsearch.cpp sphinxrt.cpp sphinxjson.cpp sphinxudf.c sphinxaot.cpp

noinst_LIBRARIES = libsphinx.a
libsphinx_a_SOURCES = $(SRC_SPHINX)

bin_PROGRAMS = indexer search spelldump indextool wordbreaker
noinst_PROGRAMS = tests

indexer_SOURCES = indexer.cpp
search_SOURCES = search.cpp
spelldump_SOURCES = spelldump.cpp
indextool_SOURCES = indextool.cpp
tests_SOURCES = tests.cpp
wordbreaker_SOURCES = wordbreaker.cpp

BUILT_SOURCES = extract-version
.PHONY: extract-version
extract-version:
	/bin/sh svnxrev.sh ..

AM_CPPFLAGS = $(LIBRE2_CFLAGS) -DSYSCONFDIR="\"$(sysconfdir)\"" -DDATADIR="\"$(localstatedir)/data\""
COMMON_LIBS = libsphinx.a $(LIBSTEMMER_LIBS) $(MYSQL_LIBS) $(PGSQL_LIBS) $(LIBRE2_LIBS)
LDADD = $(COMMON_LIBS)
