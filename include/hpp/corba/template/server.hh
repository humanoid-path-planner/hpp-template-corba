// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of hpp-template-corba
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_CORBA_SERVER_HH
# define HPP_CORBA_SERVER_HH

#include <string>
# include <omniORB4/CORBA.h>

namespace hpp
{
  namespace corba
  {
    class ServerBase
    {
    public:
      /**
	 \brief Constructor
	 \param argc, argv parameter to feed ORB initialization.

	 \note It is recommended to configure your Corba implementation through
	 environment variables and to set argc to 1 and argv to any string.
      */
      ServerBase (int argc, const char *argv[],
          const char* orb_identifier="",
          const char* options[][2]=0);

      /**
	 \name CORBA server initialization
         \{
      */
      /** Initialize ORB.
       * This is called by the constructor of this class and should not be
       * called manually.
       */
      bool initORB (int argc, const char *argv[],
          const char* orb_identifier,
          const char* options[][2]);
      bool initRootPOA(bool inMultiThread);
      bool initOmniINSPOA();
      /**
	 \}
      */

      /// \brief Shutdown CORBA server
      virtual ~ServerBase ();

      /// \brief Initialize CORBA server to process requests from clients and
      ///        declare it to the NameService (DNS for CORBA)
      /// \param contextId first part of context name
      /// \param contextKind second part of context name
      /// \param objectId first part of CORBA server name
      /// \param objectKind second part of CORBA server name
      /// \return 0 if success, -1 if failure.
      ///
      /// The CORBA server is referenced in the name server by context and
      /// name: contextId.contextKind/objectId.objectKind.
      /// The context can be seen as a directory and the object as a filename.
      int startCorbaServer (const std::string& contextId,
			    const std::string& contextKind,
			    const std::string& objectId,
			    const std::string& objectKind);

      /// \brief Initialize CORBA server to process requests from clients and
      ///        declare it to the NameService (DNS for CORBA)
      /// \param contextId first part of context name
      /// \param contextKind second part of context name
      /// \return 0 if success, -1 if failure.
      ///
      /// The CORBA server is referenced in the name server by context and
      /// name: contextId.contextKind.
      int startCorbaServer (const std::string& contextId,
			    const std::string& contextKind);

      /// \brief Initialize CORBA server to process requests from clients
      int startCorbaServer ();

      /// \brief If ORB work is pending, process it
      /// \param loop if true, the function never returns; if false, the function processes pending requests and returns.
      int processRequest (bool loop);

      PortableServer::POA_var main_poa ()
      {
        return main_poa_;
      }

      /// The Portable Object Adapter used to active the server
      PortableServer::POA_var poa ()
      {
        return poa_;
      }

      CORBA::ORB_var orb()
      {
        return orb_;
      }

    protected:
      CORBA::ORB_var orb_;
      PortableServer::POA_var poa_, main_poa_, ins_poa_;

      /// \brief Corba context.
      CosNaming::NamingContext_var hppContext_;

      void setServant(CORBA::Object_ptr obj);

    private:
      /// \brief Implementation of object
      CORBA::Object_var servant_;

      /// \brief Create context.
      bool createHppContext (const std::string& id, const std::string kind);

      /// \brief Store objects in Corba name service.
      bool bindObjectToName (CORBA::Object_ptr objref,
			     CosNaming::Name objectName);

      /// \brief Store objects in Corba name service.
      bool bindObjectToName (CosNaming::NamingContext_ptr context,
          CORBA::Object_ptr objref,
          CosNaming::Name objectName);
    };

    /**
       \brief Template CORBA server
       
       For information on how to use see the \ref hpp_template_corba_sec_how_to
       section of the main documentation page
    */
    template <class T> class Server : public ServerBase
    {
    public:
      /**
	 \brief Constructor
	 \param argc, argv parameter to feed ORB initialization.

	 \note It is recommended to configure your Corba implementation through
	 environment variables and to set argc to 1 and argv to any string.
      */
      Server (int argc, const char *argv[],
          const char* orb_identifier="",
          const char* options[][2]=0);

      /**
	 \name CORBA server initialization
         \{
      */
      /** Initialize a root POA
       * This is suitable for multithreading and for using a name service.
       * \param inMultiThread whether the server may process request using
       *        multithread policy.
       */
      bool initRootPOA(bool inMultiThread);
      /** Initialize a root POA
       * This cannot be multithreaded. It is suitable to serve an object at a
       * fixed address. The address can be set using the ORB endPoint option.
       * \param object_id the object name, use in the address (corbaloc:iiop:host:port/object_id)
       */
      bool initOmniINSPOA(const char* object_id);
      /**
	 \}
      */

      /// \brief Shutdown CORBA server
      ~Server ();

      /// \brief Return a reference to the implementation
      T& implementation();

    private:
      T* impl_;

      /// \brief It seems that we need to store this object to
      /// deactivate the server.
      PortableServer::ObjectId_var servantId_;

      /// \brief Corba context.
      CosNaming::NamingContext_var hppContext_;

      /// \brief Create context.
      bool createHppContext (const std::string& id, const std::string kind);

      /// \brief Store objects in Corba name service.
      bool bindObjectToName (CORBA::Object_ptr objref,
			     CosNaming::Name objectName);

      /// \brief Store objects in Corba name service.
      bool bindObjectToName (CosNaming::NamingContext_ptr context,
          CORBA::Object_ptr objref,
          CosNaming::Name objectName);


      /// \brief Deactivate and destroy servers
      ///
      /// Destroying active servers raises a Corba exception.
      void deactivateAndDestroyServers ();
    };

  } // end of namespace corba.
} // end of namespace hpp.

#include "hpp/corba/template/server.hxx"
#endif
