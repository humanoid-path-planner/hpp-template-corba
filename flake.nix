{
  description = "This package is intended to ease construction of CORBA servers by templating actions that are common to all servers";

  nixConfig = {
    extra-substituters = [ "https://gepetto.cachix.org" ];
    extra-trusted-public-keys = [ "gepetto.cachix.org-1:toswMl31VewC0jGkN6+gOelO2Yom0SOHzPwJMY2XiDY=" ];
  };

  inputs = {
    nixpkgs.url = "github:nim65s/nixpkgs/gepetto";
    flake-parts = {
      url = "github:hercules-ci/flake-parts";
      inputs.nixpkgs-lib.follows = "nixpkgs";
    };
    hpp-util = {
      url = "github:humanoid-path-planner/hpp-util";
      inputs.nixpkgs.follows = "nixpkgs";
      inputs.flake-parts.follows = "flake-parts";
    };
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [ ];
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "aarch64-darwin"
        "x86_64-darwin"
      ];
      perSystem =
        {
          self',
          pkgs,
          system,
          ...
        }:
        {
          packages = {
            inherit (pkgs) cachix;
            default = pkgs.callPackage ./. { hpp-util = inputs.hpp-util.packages.${system}.default; };
          };
          devShells.default = pkgs.mkShell { inputsFrom = [ self'.packages.default ]; };
        };
    };
}
