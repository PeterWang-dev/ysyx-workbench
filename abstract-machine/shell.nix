{
  pkgs ? import (fetchTarball "https://nixos.org/channels/nixos-25.11/nixexprs.tar.xz") { },
  nemu-env ? null,
  npc-env ? null,
}:
let
  pkgsCross = pkgs.pkgsCross.riscv32;
  am = pkgsCross.callPackage ./default.nix { };
in
pkgs.mkShell rec {
  name = "am-env";
  inputsFrom = [ am ];
  packages = [ ];
  shellHook = ''
    export AM_HOME=${AM_HOME}
  '';
  AM_HOME = toString ./.;
}
