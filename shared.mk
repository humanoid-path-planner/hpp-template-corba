# Add shared dependencies.
AM_CPPFLAGS +=			\
	-I$(top_builddir)/idl	\
	$(HRP2_CFLAGS)	\
	$(HPP_UTIL_CFLAGS)	\
	$(OMNIORB4_CFLAGS)

AM_LDFLAGS +=			\
	$(HRP2_LDFLAGS)	\
	$(OMNIORB4_LDFLAGS)
