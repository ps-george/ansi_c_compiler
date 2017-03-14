Test Deliverable
================

You need test programs in order to check whether your compiler
emits code that actually works. Writing test-cases is quite
a skill, and it is very difficult to get good test coverage.
As much as possible you should develop independent test-cases
which look at individual features you are working on. Also, once
a test-case is successfully passed, no future features should
stop that test-case passing. The situation where the addition
of something new stops something old working is generally
called a _regression_, and _regression testing _is used to
make sure that functionality doesn't go backwards.

In order to do regression testing, you need two things:

1 - A set of test-cases.

2 - An automated system for running the test-cases.

A simple version of the latter will be developed in the
lecture, then committed here. Your job is to develop ten
test cases looking for different functionality. There is
no requirement that your compiler implements these features, only
that your test-cases try to test them.

The testing process shown in the lecture has been captured
as an automated script in `run_test_deliverable.sh`. You
can test your compiler simply by doing:
````
run_test_deliverable.sh
````
or you can test against a different compiler by doing:
````
run_test_deliverable.sh path_to_your_compiler
````
Any compiler under test must support the same IO as yours (i.e.
C comes in over stdin, assembly goes out over stdout).

Test case format
----------------

Each test case has a name ${NAME}, and consists of two files:

- `${NAME}.c` : The source file to be compiled by the compiler under test.
  This should be very minimal, and use the smallest amount of code needed
  to perform the test.

- `${NAME}_driver.c` : A driver file to be compiled by GCC, which knows how
  to invoke the functionality in the tested file. This can contain any
  C code at all, as it will be compiled by GCC.

The testing process for a test-case is then:

1 - Compile `${NAME}.c` using the compiler under test into assembly.

2 - Compile `${NAME}_driver.c` using MIPS GCC.

3 - Link the generated assembly and the driver object into a MIPS executable.

4 - Run the executable under QEMU

5 - If the executable returns 0 (via `$?` in the shell), then the test-case has passed.

If any of these steps fail, then either the test-case is malformed,
or the compiler under test is not generating correct code.

There are a number of basic test-cases already included.

Required tests
--------------

The requirements for the deliverable are to create ten tests:

1 - IFT : Can the compiled code correctly execute a branch of an if.

2 - IFF : Can the compiled code correctly not execute a branch of an if.

3 - IFELSET : Test that an if else condition correctly executes the true branch.

4 - IFELSEF : Test that an if else condition correctly executes the false branch.

5 - WHILE0 : Check that a while loop can execute zero times.

6 - WHILEN : Check that a while loop can execute more than once.

7 - RECURSION : A minimal test that recursive function calls work.

8 - GLOBAL : Check that global variables can be shared between object files.

9 - MAIN : Check that the compiler under test can emit a valid `main` entry point.

10 - ATOI : Check that the generated code can call the C function `atoi` (note
    that `atoi` is just a function, so all you need is the declaration for
    `atoi` - you don't need to be able to handle all of the C standard library
    header).

Note that these tests do not reflect either a required level
of achievement for your compiler, nor should they mean that
you can't add other tests.

Submitted files
---------------

Your tests cases should be included in a folder called

    test_deliverable/test_cases

and follow the naming convention in the example files.

Notes on additional testing
---------------------------

- You are not required to use this testbench, as it has pretty
  limited functionality.

- The only required deliverables are the test-case files. You
  can modify the script if you wish.
  
