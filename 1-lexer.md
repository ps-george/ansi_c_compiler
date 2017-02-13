Create a tokeniser for the C language.
======================================

Your program should accept C source code on
`stdin` and write the tokens out to `stdout`
in [JSON](http://www.json.org).

Informal compilation runs
-------------------------

I'll do some compilation-only runs, which simply check that
your submission compiles and doesn't immediately crash. The
points at which I'll grab hashes from blackboard is:

- Sunday 5th Feb, 22:00

- Monday 6th Feb, 22:00

These runs will not help you debug your lexer, they are
only to give you some peace-of-mind that your build
automation is correct.

Input format
------------

The input file will be pre-processed [ANSI C](https://en.wikipedia.org/wiki/ANSI_C),
also called C90 or C89. It's what's generally thought of as "classic" or "normal" C,
but not the _really_ old one without function prototypes (you may never have come
across that). C90 is still often used in embedded systems, and pretty much the
entire linux kernel is in C90.

We've mainly taught you C++, but you're probably aware of C as a subset of C++ without
classes, which is a good mental model. Your programs (lexer, parser and compiler) will
never be given code that has different parsing or execution semantics under C and C++ (so for
example I won't give you code that uses "class" as an identifier).

The source code will not contain any compiler-specific or platform-specific
extensions. If you pre-process a typical program (see later), you'll see many
things such as `__attribute__` or `__declspec` coming from the system headers. You will
not need to deal with any of these[^1].

The test inputs will be a set of files of increasing complexity and
variety. The initial files will contain a small number of basic tokens,
then the lexicon will be increased, and finally Pre-Processor directives
(see next section) will be included. All files will be [well-formed](https://en.wikipedia.org/wiki/Well-formedness).

Output Format
-------------

You will be outputting the tokens as [JSON](http://www.json.org/),
which is a lightweight way of representing structured data. A JSON
value can be either:

- An array of JSON values

- A dictionary that maps names to JSON values

In your output format we will use a dictionary to represent each
token, and the top-level output will be an array of those dictionaries.

Each dictionary should have the following properties:

- "Text" : The original text of the token, not including any
  surrounding white-space. A special case is made for string literals, where
  the surrounding '"'s can be omitted, though if they are included (appropriately
  escaped) it [is fine too](#2).

- "Class" : Describes the class of token, with one of the following classes:

  - "Keyword" : `while`, `if`, ...

  - "Identifier" : `x`, `y`, `x6`, ...

  - "Operator" : `(`, `[`, `+`

  - "Constant" : `42`, `1.0`, `'x'`, `' '`...

  - "StringLiteral" : `"Is it too late now to say sorry?"`, `"Cause I'm missing more than just"`, ...

  - "Invalid" : An unknown token type.

  *Note*: This does not make any distinction between "operators" and
  "punctuators" which you will see in some C grammars. We will ignore
  the distinction and only have an operator class.

- "StreamLine" : The line number the token appears on, in terms of the input
  stream. The first line number is 1. This number increases regardless of any
  remapping indicated by pre-processor directives.

- "SourceFile" : The source file the token came from. See [Pre-Processor section](#Pre-Processor)
  for details on file-names - if you do not support file-names, then do not
  include this dictionary property.

- "SourceLine" : The source line the token came from. See [comments on the pre-processor](#Pre-Processor).

- "SourceCol" : The source column the token started at. If a token starts at the
  first character on a line, it would have `"SourceCol":1`. Column offsets
  should follow the [GNU error message guidelines](https://www.gnu.org/prep/standards/standards.html#Errors).

Any entry of the token dictionary not supported by your lexer
can be omitted, and the results for the rest will still be assessed.

You may optionally include an empty final '{}' entry in the array
of tokens, which makes it a little easier to print out.

Program build
-------------

From your top-level directory, doing:

    make bin/c_lexer

should create a programe called... `bin/c_lexer`.
How the makefile makes it is up to you.

You are free to use C or C++ (or something else if it
is installed in the target environment), and may make use
of other tools such as flex as part of your
build process. The target environment is the lab
Ubuntu distribution (Ubuntu 16.04), or equivalently an
Ubuntu 16.04 VM as configured in the attached Vagrantfile.

If you particularly want to use a tool/language, then
submit a pull request againt the Vagrantfile - as long
as they are reasonable, they can be added in (though they
will not then magically appear in the lab...)

Example
-------

Assuming you are in a console in the current directory,
this would be an example session:
````
$ make bin/c_lexer
$ echo "int x;" > wibble.c
$ cat wibble.c
int x;
$ cat wibble.c | bin/c_lexer
[
{"Text":"int","Class":"Keyword"}
,
{"Text":"x","Class":"Identifier"}
,
{"Text":";","Class":"Operator"}
]
````

Another session for a different lexer could be:
````
$ make bin/c_lexer
$ echo "float x=" > wibble.c
$ echo "  4.5 ;" >> wibble.c
$ cat wibble.c
float x=
  4.5 ;
$ 
$ cat wibble.c | bin/c_lexer
[ { "Class" : "Keyword",    "Text": "float", "StreamLine" : 1, "SourceCol" : 1 },
  { "Class" : "Identifier", "Text": "x",     "StreamLine" : 1, "SourceCol" : 7 },
  { "Class" : "Operator",   "Text": "=",     "StreamLine" : 1, "SourceCol" : 8 },
  { "Class" : "Constant",   "Text": "4.5",   "StreamLine" : 2, "SourceCol" : 3 },
  { "Class" : "Operator",   "Text": ";",     "StreamLine" : 2, "SourceCol" : 7 },
  {}
]
````

Note that both examples do not have the full complement of fields, and
the first example does not use a final empty token, while the second does.

The outputs also look different because we are using JSON as
a container, so the exact spacing of things doesn't matter
too much. Also within the dictionary (the parts within `{}`)
the ordering of `key:value` pairs does not matter. However,
the ordering of tokens within the toplevel array `[]` _does_
matter.

There is some [ambiguity](#2) over the string literals, which might
or might not include the quotes. _Both_ forms will be accepted as
value, so another session for a different lexer could be (preferred):
````
$ cat wibble.c
z="wibble"
$ cat wibble.c | bin/c_lexer
[ { "Class" : "Identifier",    "Text": "z" },
  { "Class" : "Operator",    "Text": "=" },
  { "Class" : "StringLiteral",    "Text": "wibble" }
]
````
or
````

$ cat wibble.c | bin/c_lexer
[ { "Class" : "Identifier",    "Text": "z" },
  { "Class" : "Operator",    "Text": "=" },
  { "Class" : "StringLiteral",    "Text": "\"wibble\"" }
]
````

Pre-Processor
-------------

TLDR : if you don't want to support pre-processor information, then
if you encounter a `#` character that is _not_ in a string literal,
consume all characters to the end of the line.

If needed, the input will already have been pre-processed, which means
that all instances `#define` and `#include` will already have been processed. However,
you may still see some input lines from the pre-processor. Create a simple
file called `tmp.c`:

    echo -e "#include <stdio.h>\nint main(){\n  printf(\"Wibble\"); \n}\n" > tmp.c
    less tmp.c

We can now pre-process it with `cpp`, the [GNU C Pre-Processor](https://gcc.gnu.org/onlinedocs/cpp/):

    cpp tmp.c

You should should see a load of stuff from the standard includes, then
your tiny program at the bottom. You can get a better look with `less`:

    cpp tmp.c | less

At the top of the file you'll see something like `# 1 tmp.c`, then
references to various files like `/usr/include/stdio.h` and `/usr/include/sys/config.h`.
If you scroll down, eventually you'll see the first non-empty line that
_doesn't_ start with `#` - in my case it is `typedef signed char __int8_t;`,
but it could be something else. This represents the first true token,
and will be the first line that should cause a token to be output.

The format of the `#` lines is explained in the [Pre-Processor Manual](https://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html),
though you can get a good sense of what is going on by comparing
the original headers and the output of `cpp`. `less` has a mode
the displays line numbers (the `-N` option), so do:

    cpp tmp.c | less -N

in one terminal, and in another terminal do:

    less -N /usr/include/stdio.h

It gives quite a good insight into how the transformation
happens, as you can match up the lines in the original
versus the lines in the `#` output, and see where comments
and `#define`s have been removed.

Note: there is no requirement that the input has been pre-processed,
so there may be no `#` lines at all. Use the default filename
"<stdin>" as the SourceFile if there is no information provided
by a pre-processor.

Footnotes
=========

[^1] - Some thought indicates _why_ you won't see extensions. Things
       like `__attribute__` are a side-channel between the implementer
       of the C run-time and the compiler, or the OS interface and the
       compiler. It is necessary that both sides agree on what those
       extensions mean, so for example the writers of `libc` have to talk
       to the writers of `gcc` about what they need and why. The C
       standard recognises that this is necessary, and so explicitly reserves
       identifiers beginning with two under-scores as "implementation defined",
       where "implementation" means the compiler.

       So in this instance _you_ are the implementation. Given you have
       not defined any extensions, logically there are no possible extensions
       that could occur.
