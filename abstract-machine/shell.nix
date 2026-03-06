{
  pkgs ? import (fetchTarball "https://nixos.org/channels/nixos-25.11/nixexprs.tar.xz") { },
  nemu-env,
  npc-env,
}:
let
  pkgsCross = pkgs.pkgsCross.riscv32;

  # ! WARNING: am is a riscv32 package, that is, if use
  # ! 'pkgsCross.callPackage ... { }' directly, the setup phrase of
  # ! this package may include riscv32 libraries and modify NIX_LD_FLAGS
  # ! that brought by dependencies, which may cause unexpected build behavior!
  # ! Meanwhile, devShell is hybrid, both for native and cross compile!
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
