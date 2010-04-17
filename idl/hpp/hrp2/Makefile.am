include $(top_srcdir)/build-aux/init.mk

IDL_DIRECTORY= $(IDL_PREFIX)/hpp/hrp2
IDL_GUARD_PREFIX = "HRP2_SERVER_"
include $(top_srcdir)/build-aux/idl.mk

include $(top_srcdir)/shared.mk

# Compile stubs separately to save recompilation time.
# Do *not* include C++ warnings as generated code triggers
# some (-Werror would then make the compilation fail).
noinst_LTLIBRARIES = libcorba-stubs.la
nodist_libcorba_stubs_la_SOURCES =	\
	hrp2.stub.cc			\
	hrp2.stub.hh

libcorba_stubs_la_LIBADD = $(OMNIORB4_LIBS)
