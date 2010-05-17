// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hrp2-server.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <iostream>

#include <hpp/util/debug.hh>

#include "hrp2.impl.hh"
#include "server-private.hh"

//FIXME: remove me.
#define HPPCI_CATCH(msg, ret)						\
  catch(CORBA::SystemException&) {					\
    hppDout (error, "CORBA::SystemException: " << msg);	\
    return ret;								\
  }									\
  catch(CORBA::Exception&) {						\
    hppDout (error, "CORBA::Exception: " << msg);	\
    return ret;								\
  }									\
  catch(omniORB::fatalException& fe) {					\
    hppDout (error, "CORBA::fatalException: " << msg);	\
    return ret;								\
  }									\
  catch(...) {								\
    hppDout (error, "CORBA: unknown exception: " << msg);	\
    return ret;								\
  }

namespace hpp
{
  namespace corba
  {
    namespace impl
    {
    } // end of namespace impl.
  } // end of namespace hrp2Server.
} // end of namespace hpp.
