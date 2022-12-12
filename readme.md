# recombine
*simple python tool which combines local C/C++ source/headers into one file*

___

## how to use
```shell
$ python3 -m recombine -h
```
```shell
usage: recombine [-h] [-o OUTPUT_FILE] [-d DIRECTORY] [-f CONFIG_FILE] [-v]

aggregate multiple C/C++ source files into one

options:
  -h, --help            show this help message and exit
  -o OUTPUT_FILE, --output OUTPUT_FILE
                        output filename, 'answer.cpp' by default
  -d DIRECTORY, --directory DIRECTORY
                        directory containing source files, current directory by default
  -f CONFIG_FILE, --config CONFIG_FILE
                        YAML file describing the files which need to be combined together
  -v, --verbose         print debug information during the process on the standard output
```

## custom preprocessor
* imports and expands local headers (limitation: all `#include` using `"quotes"` must be present)
* keeps system headers
* understands preprocessor macro definitions (`#define` and `#undef`)
* replaces macros
* understands preprocessor logic around macro definitions (`#ifdef MACRO`, `#ifndef MACRO`, `#if defined(MACRO)` and `#if not defined(MACRO)`)
* *does **not** process general `#if` preprocessor instruction*

___

## development validation

TODO: move to CI
* generate a recombined version of the test project:

  ```shell
  $ python3 -m recombine -o test/recombined/recombined.h -d test/original -f test/recombine.yaml
  ```

* build and validate the result (unit tests expect different results from original and recombined by design)

  ```shell
  $ cmake --build build --config Debug --target all -j 6 --
  $ ctest -j6 -C Debug -T test --output-on-failure
  ```

* test the diff between result and expectations

  ```shell
  $ diff test/expected.cpp test/recombined/recombined.h
  ```