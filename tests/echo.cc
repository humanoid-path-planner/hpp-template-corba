#include <hpp/corba/template/server.hh>

// files tests/echo.hh and tests/echoSK.cc are generated at compile time using
// omniidl -bcxx echo.idl
#include "tests/echo.hh"

class Echo_i : public POA_Echo {
 public:
  inline Echo_i() {}
  virtual ~Echo_i() {}
  virtual char* echoString(const char* mesg);
};

char* Echo_i::echoString(const char* mesg) { return CORBA::string_dup(mesg); }

int main() {
  hpp::corba::Server<Echo_i> server(0, NULL);
  server.initRootPOA(true);
  server.startCorbaServer();
  return 0;
}
