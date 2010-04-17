// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hrp2-server.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HRP2_SERVER_HRP2_IMPL_HH
# define HRP2_SERVER_HRP2_IMPL_HH
# include "hpp/hrp2/fwd.hh"
# include "hpp/hrp2/hrp2.stub.hh"

namespace hpp
{
  namespace hrp2Server
  {
    namespace impl
    {
      /// \brief Implementation of corba interface ChppciRobot.
      ///
      /// The construction of a 
      class Hrp2 : public virtual POA_hpp::Hrp2
      {
      public:
	Hrp2 (hrp2Server::Server* server);
      
	virtual Short Init(Boolean initp) throw (SystemException);

	/// \brief Pointer to the object owning this
	hrp2Server::Server* server_;

      };
    } // end of namespace impl.
  } // end of namespace hrp2Server.
} // end of namespace hpp.

#endif
