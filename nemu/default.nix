{
  stdenv,
  llvmPackages,
  bison,
  flex,
  readline,
  SDL2,
  SDL2_ttf,
  SDL2_image,
  dtc,
}:
stdenv.mkDerivation {
  pname = "nemu";
  version = "0.1.0";
  src = ./.;
  nativeBuildInputs = [
    bison
    flex
  ];
  buildInputs = [
    llvmPackages.llvm
    readline
    dtc
    SDL2
    SDL2_ttf
    SDL2_image
  ];
}
