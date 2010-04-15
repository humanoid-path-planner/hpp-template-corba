// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <iostream>

#include <hpp/util/debug.hh>
#include "hpp/corbaserver/server.hh"

#include "hrp2.impl.hh"

#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#include "config.h"

namespace hpp
{
  namespace corbaServer
  {
    namespace impl
    {
      Hrp2::Hrp2(corbaServer::Server* server) :
	server_(server)
      {};
      
      Short Hrp2::Init(Boolean initp)
	throw (SystemException)
      {
	std::cout << "Hrp2::Init(" << initp << ")" << std::endl;
	return 0;
      }
    } // end of namespace impl.
  } // end of namespace corbaServer.
} // end of namespace hpp.
