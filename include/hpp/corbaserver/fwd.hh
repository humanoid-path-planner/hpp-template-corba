// Copyright (C) 2010 by Thomas Moulard, CNRS.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HRP2_SERVER_FWD_HH
# define HRP2_SERVER_FWD_HH

//FIXME: should be replaced by CORBA base types forward declarations.
# include <omniORB4/CORBA.h>

namespace hpp
{
  namespace corbaServer
  {
    class Server;

    namespace impl
    {
      using CORBA::Boolean;
      using CORBA::Double;
      using CORBA::Short;
      using CORBA::SystemException;
      using CORBA::ULong;
      using CORBA::UShort;

      class Hrp2;
      class Server;

      class InternalCorbaObject;
    }
  } // end of namespace corbaServer.
} // end of namespace hpp.

#endif //! HRP2_SERVER_FWD_HH
