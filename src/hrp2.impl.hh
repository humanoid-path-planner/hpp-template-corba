// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_CORBASERVER_HRP2_IMPL_HH
# define HPP_CORBASERVER_HRP2_IMPL_HH
# include "hpp/corbaserver/fwd.hh"
# include "hpp/corbaserver/hrp2.stub.hh"

namespace hpp
{
  namespace corbaServer
  {
    namespace impl
    {
      /// \brief Implementation of corba interface ChppciRobot.
      ///
      /// The construction of a 
      class Hrp2 : public virtual POA_hpp::Hrp2
      {
      public:
	Hrp2 (corbaServer::Server* server);
      
	virtual Short Init(Boolean initp) throw (SystemException);

	/// \brief Pointer to the object owning this
	corbaServer::Server* server_;

      };
    } // end of namespace impl.
  } // end of namespace corbaServer.
} // end of namespace hpp.

#endif
