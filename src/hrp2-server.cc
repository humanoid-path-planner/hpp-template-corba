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

using hpp::hrp2Server::Server;

int
main (int argc, const char* argv[])
{
  Server server (argc, argv, true);

  if (server.startCorbaServer () < 0)
    hppDoutFatal (error, "failed to start CORBA server");
  server.processRequest(true);
}
