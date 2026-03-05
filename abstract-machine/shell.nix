{
  pkgs ? import (fetchTarball "https://nixos.org/channels/nixos-25.11/nixexprs.tar.xz") { },
  nemu-env,
  npc-env,
}:
let
  # ! Must use buildPackages otherwise LD_LIBRARY_PATH would be interfered
  pkgsCross = pkgs.pkgsCross.riscv32.buildPackages;
  am = pkgsCross.callPackage ./default.nix { };
in
pkgs.mkShell rec {
  name = "am-env";
  inputsFrom = [
    am
    nemu-env
    npc-env
  ];
  packages = [ ];
  shellHook = ''
    export AM_HOME=${AM_HOME}
  '';
  AM_HOME = toString ./.;
}
