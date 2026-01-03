{
  pkgs ? import (fetchTarball "https://nixos.org/channels/nixos-25.11/nixexprs.tar.xz") { },
}:
let
  nemu = pkgs.callPackage ./default.nix { };
in
pkgs.mkShell rec {
  name = "nemu-dev";
  inputsFrom = [ nemu ];
  packages = [ ];
  shellHook = ''
    export NEMU_HOME=${NEMU_HOME}
  '';
  NEMU_HOME = toString ./.;
}
