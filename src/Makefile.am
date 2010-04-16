include $(top_srcdir)/build-aux/init.mk
include $(top_srcdir)/shared.mk

# Add available warnings flags.
AM_CXXFLAGS += $(WARNING_CXXFLAGS)

# Corba server library.
lib_LTLIBRARIES = libhrp2-server.la

libhrp2_server_la_SOURCES =		\
	hrp2.impl.cc 			\
	hrp2.impl.hh 			\
	server.cc 			\
	server-private.cc 		\
	server-private.hh

libhrp2_server_la_LIBADD = 					\
	$(top_builddir)/idl/hpp/hrp2/libcorba-stubs.la	\
	$(HPP_UTIL_LIBS)					\
	$(HRP2_LIBS)

# Corba server executable.
bin_PROGRAMS = hrp2-server
hrp2_server_SOURCES = hrp2-server.cc
hrp2_server_LDADD = libhrp2-server.la

# Python bindings
PYTHON_MODULENAME=hpp_hrp2

OMNIIDLFLAGS =						\
		-I $(top_srcdir)/idl/hpp/hrp2 \
		-bpython				\
		-Wbpackage=$(PYTHON_MODULENAME)

hppPythondir = $(DESTDIR)$(prefix)/$(PYTHON_SITELIB)

nobase_hppPython_DATA = 			\
	hpp_hrp2/hrp2_idl.py

nobase_hppPython_DATA += 			\
	hpp/__init__.py				\
	hpp/hrp2/__init__.py		\
	hpp/hrp2/client.py		\
	hpp/hrp2/problem.py		\
	hpp/hrp2/walk.py

install-data-local:
	$(MKDIR_P) "$(hppPythondir)/hpp_hrp2/"
	cp -rf hpp_hrp2/ "$(hppPythondir)"

hpp_hrp2/%_idl.py:	\
		$(top_builddir)/idl/hpp/hrp2/%.idl \
		$(top_builddir)/config.status
	$(OMNIIDL) $(OMNIIDLFLAGS) "$<"

clean-local:
	rm -rf hpp_hrp2
