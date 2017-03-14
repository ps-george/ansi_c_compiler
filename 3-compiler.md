Create a compiler for the C language
====================================

Your program should accept C source code on
`stdin` and write a heirarchical representation on `stdout`.

Input Format
------------

The input format is C90.

Output Format
-------------

The output format should be MIPS1 assembly code.

It should be possible to assemble and link this code
against a C run-time, and have it execute correctly
on a MIPS processor as emulated by `qemu-mips`.

Compilation
-----------

Your compiler should be built using:
````
make bin/c_compiler
````
and the resulting program should be called `bin/c_compiler`.

The target environment remains Ubuntu 16.04.

Deliverables
------------

There are actually three deliverables here:

1 - The compiler itself

2 - A [test framework](3-compiler-test_deliverable.md)

3 - [Documentation](3-compiler-documentation.md)

