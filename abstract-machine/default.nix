{
  stdenvNoCC,
  gcc-unwrapped,
  binutils,
}:
stdenvNoCC.mkDerivation {
  pname = "am";
  version = "0.1.0";
  src = ./.;
  nativeBuildInputs = [
    gcc-unwrapped
    binutils
  ];
  buildInputs = [ ];
}
