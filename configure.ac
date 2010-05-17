# Don't expend macros beginning by JRL_.
m4_pattern_forbid([^JRL_])
AC_PREREQ([2.63])

## --------------------- ##
## Package configuration ##
## --------------------- ##
AC_INIT([hpp-template-corba],
        [m4_esyscmd(build-aux/git-version-gen .tarball-version)],
	[hpp@laas.fr],
	[hpp-template-corba])

# Auxiliary files.
AC_CONFIG_AUX_DIR([build-aux])

# Automake.
AM_INIT_AUTOMAKE([1.9.6 dist-bzip2 -Wall nostdinc])

## ------------- ##
## C++ compiler  ##
## ------------- ##

# Search for a C++ compiler.
AC_LANG([C++])
AC_PROG_CXX

# Speed-up compilation.
if test "$GXX" = yes; then
  CXXFLAGS="$CXXFLAGS -pipe"
fi

# Customize warnings.
JRL_CXX_WARNINGS([[-Wall],
                   [-Wcast-align],
                   [-Wcast-qual],
                   [-Wformat],
                   [-Wmissing-prototypes],
                   [-Wstrict-prototypes],
                   [-Wwrite-strings],
                   [-Wbad-function-cast],
                   [-Wmissing-declarations],
                   [-Wnested-externs]])

# Macros are stored in build-aux.
AC_CONFIG_MACRO_DIR([build-aux])

## ------------------- ##
## Additionnal tools.  ##
## ------------------- ##

# Search for misc. common tools.
AC_PROG_MKDIR_P
AC_PROG_SED

# Search for omniidl.
AC_ARG_VAR([OMNIIDL], [the omniORB idl compiler])
AC_CHECK_PROGS([OMNIIDL], [omniidl])
if test x"$OMNIIDL" = x; then
 AC_MSG_ERROR([failed to find omniidl])
fi

# Search for Doxygen.
JRL_PROG_DOXYGEN

# Search for Libtool.
LT_INIT

AC_ARG_ENABLE([hpp-util],
	[AS_HELP_STRING([--enable-hpp-util],
	[use hpp-util for debug and log handling])],
	[AC_DEFINE([HPP_CORBA_ENABLE_HPP_UTIL], [1],
           [Define to 1 if hpp-util is enabled.])
	   enable_hpp_util=true]
)
AM_CONDITIONAL([HPP_UTIL], [test x$enable_hpp_util = xtrue])

# Search for pkg-config dependencies.
JRL_PKGCONFIGCHECK_ADDDEP([OMNIORB4], [omniORB4])
if test x$enable_hpp_util = xtrue; then
   JRL_PKGCONFIGCHECK_ADDDEP([HPP_UTIL], [hpp-util])
AC_SUBST([HPP_CORBA_ENABLE_HPP_UTIL], [1])
else
AC_SUBST([HPP_CORBA_ENABLE_HPP_UTIL], [0])
fi

# Generate ``config.hh'' header file.
AC_SUBST([PACKAGE_CPPNAME],
 [`echo "$PACKAGE_TARNAME" \
  | tr '@<:@:lower:@:>@' '@<:@:upper:@:>@' | sed 's/-/_/g'`])
AC_CONFIG_FILES([include/hpp/corba/config.hh])

## ------------ ##
## Test-suite.  ##
## ------------ ##

AC_CONFIG_TESTDIR([tests])
AM_MISSING_PROG([AUTOM4TE], [autom4te])

## ------------ ##
## Pkg-config.  ##
## ------------ ##

AC_SUBST([PKGCONFIG_DESCRIPTION], ['Template CORBA server'])
AC_SUBST([PKGCONFIG_URL], [])
AC_SUBST([PKGCONFIG_REQUIRES], [`echo "$PKGCONFIG_REQUIRES" | sed 's/, $//'`])
AC_SUBST([PKGCONFIG_CONFLICTS], [])
AC_SUBST([PKGCONFIG_LIBS], [])
AC_SUBST([PKGCONFIG_CFLAGS], [])


## -------------- ##
## Write output.  ##
## -------------- ##

# Create config.h
AC_CONFIG_HEADERS([config.h])

# Create Makefiles.
AC_CONFIG_FILES([
  Makefile
  include/Makefile
  include/hpp/corba/debug.hh
  doc/Makefile
])

# Write files.
AC_OUTPUT
