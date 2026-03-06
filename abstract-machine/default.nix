{
  stdenvNoCC,
  gcc,
  binutils,
}:
stdenvNoCC.mkDerivation {
  pname = "am";
  version = "0.1.0";
  src = ./.;
  nativeBuildInputs = [
    gcc
    binutils
  ];
}
