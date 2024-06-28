{
  lib,
  stdenv,
  cmake,
  hpp-util,
  jrl-cmakemodules,
  omniorb,
  pkg-config,
}:

stdenv.mkDerivation {
  pname = "hpp-template-corba";
  version = "5.0.0";

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

  strictDeps = true;

  nativeBuildInputs = [
    cmake
    pkg-config
  ];
  propagatedBuildInputs = [
    jrl-cmakemodules
    hpp-util
    omniorb
  ];

  doCheck = true;

  meta = {
    description = "This package is intended to ease construction of CORBA servers by templating actions that are common to all servers";
    homepage = "https://github.com/humanoid-path-planner/hpp-template-corba";
    license = lib.licenses.bsd3;
    maintainers = [ lib.maintainers.nim65s ];
  };
}
