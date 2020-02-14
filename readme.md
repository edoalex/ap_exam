# Advanced Programming Exam

By *Edoardo Alessandroni*, *Alberto Luvisutto* e *Andrea Mecchina*.

A collaborative work repository for the [Advanced Programming course](https://github.com/asartori86/advanced_programming-2018-19) exam of the DSSC master degree.

The whole project works with both the `c++` and the `clang` compilers. The project is subdivided in the following repositories:

+ `include`, which contains the source files related to the implementation of the binary search tree,
+ `benchmark`, which contains all the material related to the benchmarking tests performed,
+ `docs`, which contains all the material needed to produce the Doxygen documentation.

The `include` directory contains even the header file `ap_error.h`, used to throw exceptions, that was not written by us. 

The `Makefile` is used to automatically compile the implementation files with `c++`. It produces an executable `exe.x` used to test all the implemented functions.

The benchmarking tests compare the average time to find a node versus the number of elements in the container, for different kinds of containers.

More information about the project are contained in the short report `report.md`.

