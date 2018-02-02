AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)

SUBDIRS = machine .

SUBLIBS = \
	$(HIPPEROS_MACH_LIB)

ADD_OBJS = \
	$(HIPPEROS_MACH_LIB)

noinst_LIBRARIES = lib.a

lib_a_SOURCES = crt0.c getreent.c
lib_a_LIBADD = $(ADD_OBJS)
lib_a_DEPENDENCIES = $(ADD_OBJS)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif

lib.a: $(lib_a_OBJECTS)
	rm -f $@
	rm -rf tmp
	mkdir tmp
	cd tmp; \
	for i in $(SUBLIBS); do \
	  $(AR) x ../$$i; \
	done;
	$(AR) $(AR_FLAGS) $@ tmp/*.o $^
	$(RANLIB) $@
	rm -rf tmp

ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
