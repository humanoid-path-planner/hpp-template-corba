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
#include "hpp/hrp2/server.hh"

#include "hrp2.impl.hh"

#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#include "config.h"

namespace hpp
{
  namespace hrp2Server
  {
    namespace impl
    {
      Hrp2::Hrp2()
      {};
      
      Short Hrp2::Init(Boolean initp)
	throw (SystemException)
      {
	std::cout << "Hrp2::Init(" << initp << ")" << std::endl;
	return 0;
      }
    } // end of namespace impl.
  } // end of namespace hrp2Server.
} // end of namespace hpp.
