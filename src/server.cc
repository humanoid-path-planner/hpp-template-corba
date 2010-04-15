// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <errno.h>
#include <pthread.h>
#include <iostream>

#include <hpp/util/debug.hh>

#include "hpp/corbaserver/server.hh"
#include "server-private.hh"


//FIXME: remove me.
#define HPPCI_CATCH(msg, ret)						\
  catch(CORBA::SystemException&) {					\
    hppDout (error, "hppCorbaServer: CORBA::SystemException: " << msg);	\
    return ret;								\
  }									\
  catch(CORBA::Exception&) {						\
    hppDout (error, "hppCorbaServer: CORBA::Exception: " << msg);	\
    return ret;								\
  }									\
  catch(omniORB::fatalException& fe) {					\
    hppDout (error, "hppCorbaServer: CORBA::fatalException: " << msg);	\
    return ret;								\
  }									\
  catch(...) {								\
    hppDout (error, "hppCorbaServer: unknown exception: " << msg);	\
    return ret;								\
  }

namespace hpp
{
  namespace corbaServer
  {
    using CORBA::Exception;
    using CORBA::Object_var;
    using CORBA::SystemException;
    using CORBA::ORB_init;
    using CORBA::PolicyList;
    using omniORB::fatalException;

    namespace
    {
      /// \brief Forward logging messages to hpp logging mechanism.
      /// If debug is disabled, CORBA logging will be disabled too.
      ///
      /// Tracing has to be enabled in your ``omniORB.cfg'' to use this
      /// feature.
      /// See ``omniORB configuration and API'' > ``Tracing options''
      /// section of omniORB manual for more information.
      void logFunction (const char* msg);

      void logFunction (const char* msg)
      {
	hppDout (info, "omniORB: " << msg);
      }
    } // end of anonymous namespace.


    Server::Server(int argc, const char *argv[], bool inMultiThread)
    {
      // Register log function.
      omniORB::setLogFunction (&logFunction);

      attPrivate = new impl::Server;

      initORBandServers (argc, argv, inMultiThread);
    }

    /// \brief Shutdown CORBA server
    Server::~Server()
    {
      attPrivate->deactivateAndDestroyServers();
      attPrivate->orb_->shutdown(0);
      delete attPrivate;
      attPrivate = NULL;
    }

    /*
      CORBA SERVER INITIALIZATION
    */

    bool Server::initORBandServers(int argc, const char* argv[],
				       bool inMultiThread)
    {
      Object_var obj;
      PortableServer::ThreadPolicy_var threadPolicy;
      PortableServer::POA_var rootPoa;

      /*
	 Fine granularity in exception handling
      */

      /*
	ORB init
      */
      try {
	attPrivate->orb_ = ORB_init (argc, const_cast<char **> (argv)); //FIXME: handle this properly.
	if (is_nil(attPrivate->orb_)) {
	  hppDout (error, "failed to initialize ORB");
	  return false;
	}
      }
      HPPCI_CATCH("failed to initialize ORB", false) /* see hppciExceptionHandlingMacros.h */

	/*
	  ORB init
	*/

	try {
	  obj = attPrivate->orb_->resolve_initial_references("RootPOA");
	}
      HPPCI_CATCH("failed to resolve initial references", false) /* see hppciExceptionHandlingMacros.h */

	/*
	  Create thread policy
	*/

	try {
	  //
	  // Make the CORBA object single-threaded to avoid GUI krash
	  //
	  // Create a sigle threaded policy object
	  rootPoa = PortableServer::POA::_narrow(obj);

	  if (inMultiThread) {
	    threadPolicy =
	      rootPoa->create_thread_policy(PortableServer::ORB_CTRL_MODEL);
	  }
	  else {
	    threadPolicy =
	      rootPoa->create_thread_policy(PortableServer::MAIN_THREAD_MODEL);
	  }
	}
      HPPCI_CATCH("failed to create thread policy", false) /* see hppciExceptionHandlingMacros.h */

	/*
	  Duplicate thread policy
	*/

	try {
	  PolicyList policyList;
	  policyList.length(1);
	  policyList[0]=PortableServer::ThreadPolicy::_duplicate(threadPolicy);

	  attPrivate->poa_ =
	    rootPoa->create_POA("child", PortableServer::POAManager::_nil(),
				policyList);

	}
      HPPCI_CATCH("failed to duplicate thread policy", false) /* see hppciExceptionHandlingMacros.h */

	/*
	  Destroy thread policy
	*/

	try {
	  // Destroy policy object
	  threadPolicy->destroy();

	}
      HPPCI_CATCH("failed to destroy thread policy", false); /* see hppciExceptionHandlingMacros.h */

      return attPrivate->createAndActivateServers(this);
    }

    int Server::startCorbaServer()
    {
      try {
	// Obtain a reference to objects, and register them in
	// the naming service.
	Object_var hrp2Obj = attPrivate->hrp2Servant_->_this();

	if (!attPrivate->createHppContext()) {
	  return -1;
	}
	// Bind hrp2Obj with name Robot to the hppContext:
	CosNaming::Name objectName;
	objectName.length(1);
	objectName[0].id   = (const char*) "hrp2";   // string copied
	objectName[0].kind = (const char*) "hpp"; // string copied

	if(!attPrivate->bindObjectToName(hrp2Obj, objectName)) {
	  return -1;
	}
	attPrivate->hrp2Servant_->_remove_ref();

	PortableServer::POAManager_var pman =
	  attPrivate->poa_->the_POAManager();
	pman->activate();
      }
      HPPCI_CATCH("failed to start CORBA server", false);
      return 0;
    }


    /// \brief If CORBA requests are pending, process them
    int Server::processRequest (bool loop)
    {
      if (loop)
	{
	  hppDout (info, "start processing CORBA requests for ever.");
	  attPrivate->orb_->run();
	}
      else
	{
	  if (attPrivate->orb_->work_pending())
	    attPrivate->orb_->perform_work();
	}
      return 0;
    }

  } // end of namespace corbaServer.
} // end of namespace hpp.
