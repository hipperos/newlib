## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

SUBDIRS = $(machine_dir) .

noinst_DATA = lib.a

lib.a: $(machine_dir)/lib.a
	rm -f $@
	ln $< $@ >/dev/null 2>/dev/null || cp $< $@

doc:

ACLOCAL_AMFLAGS = -I ../../../.. -I ../../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
