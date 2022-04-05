// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of hpp-template-corba
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_CORBA_TEMPLATE_SERVER_HXX
#define HPP_CORBA_TEMPLATE_SERVER_HXX

#include <errno.h>
#include <pthread.h>

#include <hpp/corba/template/debug.hh>
#include <iostream>

// FIXME: remove me.
#define HPP_CORBA_CATCH(msg, ret)                                        \
  catch (CORBA::UserException & exc) {                                   \
    hppCorbaDout(error,                                                  \
                 "CORBA::UserException: " << msg << " " << exc._name()); \
    return ret;                                                          \
  }                                                                      \
  catch (CORBA::SystemException&) {                                      \
    hppCorbaDout(error, "CORBA::SystemException: " << msg);              \
    return ret;                                                          \
  }                                                                      \
  catch (CORBA::Exception&) {                                            \
    hppCorbaDout(error, "CORBA::Exception: " << msg);                    \
    return ret;                                                          \
  }                                                                      \
  catch (omniORB::fatalException & fe) {                                 \
    hppCorbaDout(error, "CORBA::fatalException: " << msg);               \
    return ret;                                                          \
  }                                                                      \
  catch (...) {                                                          \
    hppCorbaDout(error, "CORBA: unknown exception: " << msg);            \
    return ret;                                                          \
  }

namespace hpp {
namespace corba {
using CORBA::COMM_FAILURE;
using CORBA::Exception;
using CORBA::Object_ptr;
using CORBA::Object_var;
using CORBA::ORB_init;
using CORBA::PolicyList;
using CORBA::SystemException;
using omniORB::fatalException;

typedef CORBA::ORB::InvalidName InvalidName;

template <class T>
Server<T>::Server(int argc, const char* argv[], const char* orb_identifier,
                  const char* options[][2])
    : ServerBase(argc, argv, orb_identifier, options), impl_(NULL) {}

/// \brief Shutdown CORBA server
template <class T>
Server<T>::~Server() {
  deactivateAndDestroyServers();
}

template <class T>
T& Server<T>::implementation() {
  return *impl_;
}

template <class T>
bool Server<T>::initRootPOA(bool inMultiThread) {
  if (!ServerBase::initRootPOA(inMultiThread)) return false;

  if (impl_ != NULL) return true;
  poa_ = main_poa();

  // create implementation
  try {
    impl_ = new T();
    setServant(impl_->_this());
  }
  HPP_CORBA_CATCH("failed to create the server implementation", false);

  // activate implementation
  try {
    servantId_ = poa_->activate_object(impl_);
  }
  HPP_CORBA_CATCH("failed to activate the server implementation", false);

  return true;
}

template <class T>
bool Server<T>::initOmniINSPOA(const char* object_id) {
  if (!ServerBase::initOmniINSPOA()) return false;

  if (impl_ != NULL) return true;
  poa_ = ins_poa_;

  // create implementation
  try {
    impl_ = new T();
    setServant(impl_->_this());
  }
  HPP_CORBA_CATCH("failed to create the server implementation", false);

  try {
    servantId_ = PortableServer::string_to_ObjectId(object_id);
    poa_->activate_object_with_id(servantId_, impl_);
  }
  HPP_CORBA_CATCH("failed to activate the server implementation", false);

  return true;
}

template <class T>
void Server<T>::deactivateAndDestroyServers() {
  if (impl_) {
    try {
      poa_->deactivate_object(servantId_);
    } catch (const CORBA::OBJECT_NOT_EXIST& exc) {
      // Servant was already deactivated and deleted.
    }
  }
}

}  // end of namespace corba.
}  // end of namespace hpp.

#endif  // HPP_CORBA_TEMPLATE_SERVER_HXX
