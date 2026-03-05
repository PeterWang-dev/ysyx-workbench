{
  stdenv,
  llvmPackages,
  ncurses,
  bison,
  flex,
  dtc,
  boost,
  readline,
  SDL2,
  SDL2_ttf,
  SDL2_image,
}:
stdenv.mkDerivation {
  pname = "nemu";
  version = "0.1.0";
  src = ./.;
  nativeBuildInputs = [
    # For menuconfig
    ncurses
    bison
    flex
    # For difftest Spike compilation
    dtc
    boost
  ];
  buildInputs = [
    llvmPackages.llvm # for disassemble support
    readline
    SDL2
    SDL2_ttf
    SDL2_image
  ];
}
