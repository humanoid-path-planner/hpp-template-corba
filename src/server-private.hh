// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hrp2-server.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HRP2_SERVER_SERVER_PRIVATE_HH
# define HRP2_SERVER_SERVER_PRIVATE_HH
# include "hpp/hrp2/fwd.hh"

# include "hrp2.impl.hh"

namespace hpp
{
  namespace corba
  {
    namespace impl
    {
      template class <T> Server
      {
      public:

	friend class hrp2Server::Server;
      };

    } // end of namespace impl.
  } // end of namespace hrp2Server.
} // end of namespace hpp.

#endif //! HRP2_SERVER_SERVER_PRIVATE_HH
