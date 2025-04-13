# Dev Utils

This folder contains the in-repo tools using in Synthesis.

``` bash
cd utils
export PATH=$(realpath ./):$PATH
```

## Change FIRRTL Compiler

You can change the FIRRTL compiler between SFC (Scala-based FIRRTL compiler)
and MFC (MLIR-based FIRRTL compiler) by modifying the `useMFC` variable in
`playground/src/Elaborate.scala`.
The latter one requires `firtool`,
which is included under `utils/` , this folder.
