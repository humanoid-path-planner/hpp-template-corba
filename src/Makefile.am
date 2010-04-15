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
	$(top_builddir)/idl/hpp/corbaserver/libcorba-stubs.la	\
	$(HPP_UTIL_LIBS)					\
	$(HRP2_LIBS)

# Corba server executable.
bin_PROGRAMS = hrp2-server
hrp2_server_SOURCES = hrp2-server.cc
hrp2_server_LDADD = libhrp2-server.la

# Python bindings
PYTHON_MODULENAME=hpp_corbaserver

OMNIIDLFLAGS =						\
		-I $(top_srcdir)/idl/hpp/corbaserver \
		-bpython				\
		-Wbpackage=$(PYTHON_MODULENAME)

hppPythondir = $(DESTDIR)$(prefix)/$(PYTHON_SITELIB)

nobase_hppPython_DATA = 			\
	hpp_corbaserver/hrp2_idl.py

nobase_hppPython_DATA += 			\
	hpp/__init__.py				\
	hpp/corbaserver/__init__.py		\
	hpp/corbaserver/client.py		\
	hpp/corbaserver/problem.py		\
	hpp/corbaserver/walk.py

install-data-local:
	$(MKDIR_P) "$(hppPythondir)/hpp_corbaserver/"
	cp -rf hpp_corbaserver/ "$(hppPythondir)"

hpp_corbaserver/%_idl.py:	\
		$(HPPCORBASERVER_PREFIX)/share/idl/hpp/corbaserver/%.idl \
		$(top_builddir)/config.status
	$(OMNIIDL) $(OMNIIDLFLAGS) "$<"

clean-local:
	rm -rf hpp_corbaserver

EXTRA_DIST += 				\
	example.py
