{
  description = "This package is intended to ease construction of CORBA servers by templating actions that are common to all servers";

  inputs.gepetto.url = "github:gepetto/nix";

  outputs =
    inputs:
    inputs.gepetto.lib.mkFlakoboros inputs (
      { lib, ... }:
      {
        overrideAttrs.hpp-template-corba = {
          src = lib.fileset.toSource {
            root = ./.;
            fileset = lib.fileset.unions [
              ./CMakeLists.txt
              ./doc
              ./idl
              ./include
              ./package.xml
              ./src
              ./tests
            ];
          };
        };
      }
    );
}
