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
  namespace hrp2Server
  {
    namespace impl
    {
      class Server
      {
      public:
	~Server ();

	/// \brief Create and activate the Corba servers.
	bool createAndActivateServers (hrp2Server::Server* server);

      private:
	CORBA::ORB_var orb_;
	PortableServer::POA_var poa_;

	/// \brief Implementation of object Hrp2
	Hrp2* hrp2Servant_;

	/// \brief It seems that we need to store this object to
	/// deactivate the server.
	PortableServer::ObjectId* hrp2Servantid_;

	/// \brief Corba context.
	CosNaming::NamingContext_var hppContext_;

	/// \brief Create context.
	bool createHppContext ();

	/// \brief Store objects in Corba name service.
	bool
	bindObjectToName
	(CORBA::Object_ptr objref, CosNaming::Name objectName);


	/// \brief Deactivate and destroy servers
	///
	/// Destroying active servers raises a Corba exception.
	void deactivateAndDestroyServers ();

	friend class hrp2Server::Server;
      };

    } // end of namespace impl.
  } // end of namespace hrp2Server.
} // end of namespace hpp.

#endif //! HRP2_SERVER_SERVER_PRIVATE_HH
