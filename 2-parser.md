Create a parser for the C language
==================================

Your program should accept C source code on
`stdin` and write a heirarchical representation on `stdout`.

Input Format
------------

The input format and constraints are the same as for the tokeniser, with
the following restrictions:

- the only variable/parameter data-type that will occur is `int` (so no arrays, structs, floats)

- the only control-flow statements are `if`, `while`, `for`, and sequencing.

- all functions are definitions (i.e. there are no declarations)

These restrictions do _not_ apply to the eventual compiler, they are
simply to make this stage more manageable as a milestone. You are
encouraged to support other things as well, but the intent here is
to get a core set of functionality fully working.

The input format is still C90, and it is worth noting
a difference between the C90 ("classic) and C99 ("modern")
languages, which is that declarations can only appear
at the top of a scope. So all variables declarations will
appear before any statements. See the later section for more discussion.

Output Format
-------------

The output format will be a heirarchical format written in 
[XML](https://en.wikipedia.org/wiki/XML), which identifies the functions, scopes, and variables.

Your output should consist of the following types of XML element:

- `<Program>` : The top-level element, containing all others.

- `<Function id="id">` : This appears within a Program element, and
    indicates the existence of a function called id. The ordering of
    Function elements relative to other globals should
    follow the original source.
    
- `<Parameter id="id">` : This appears as a child of a Function element,
    and states that the enclosing function has a parameter with this name.
    The relative ordering of Parameter elements is important, and should follow the
    order given in the function signature.
    
- `<Scope>` : Appears within either a Function or another Scope, and
    identifies a scope within which variables have a lifetime. Empty
    scopes are not considered meaningful and may be omitted or inserted
    as convenient. Extra levels of scope nesting are also allowed, as long
    as the lifetime of all variables is correct (equivalent to `((x))` == `(x)`).
    
- `<Variable>` : Appears within a Program or a Scope, and indicates a
    variable that is being introduced.
    
The output should not contain any other elements except for these
five. Each element can contain arbitrary amounts of white-space, and
you are allowed to include attributes beyond those explicitly required
here.

Examples
--------

As a simple example, the following function:

    int f( int x)
    {
        int y=x;
        return y;
    }

should result in:


    <?xml version="1.0"?>
    <Program>
        <Function id="f">
            <Parameter id="x" />
            <Scope>
                <Variable id="y" />
            </Scope>
        </Function>
    </Program>
    
or also correct would be:

    <?xml version="1.0"?>
    <Program> <Function id="f">
            <Parameter id="x" />
            <Scope />
       <Scope><Scope /></Scope>
            <Scope>
                <Scope>
                <Variable id="y" />
            </Scope></Scope>
    </Function> </Program>

and infinite variations thereof.

This code:

    int x()
    {}

    int g;

    int zz(int a, int b, int c)
    {
      if(a==b){
        int a;
        return a;
      }else{
        int fsdfsdfs;
        return c;
      }
    }

would result in:

    
    <?xml version="1.0"?>
    <Program>
        <Function id="x" />
        <Variable id="g" />
        <Function id="zz">
            <Parameter id="a" /><Parameter id="b" />
                    <Parameter id="c" />
            <Scope>
                <Scope>
                    <Variable id="a" />
                </Scope>
                <Scope>
                    <Variable id="fsdfsdfs" />
                </Scope>
            </Scope>
        </Function>
    </Program>


Given that additional scope nesting levels and extra empty scopes are
allowed, you may wonder how it is possible to tell whether the
scoping is correct. This comes down to the lifetime of variables
within the original C program. For example, given this:

    int x;
    if(...){
        int y;
    }
    
It would be possible to say:

    <Scope>
        <Variable id="x" />
        <Scope>
            <Variable id="y" />
        </Scope>
    </Scope>

as this indicates that:

- a variable x is defined.

- a variable y is defined, and x is still available within the same scope

- the variable y goes out of scope before x.

It would not be possible to say:

    <Scope>
        <Variable id="x" />
        <Variable id="y" />
    </Scope>
    
as while it matches the first two properties above, it indicates that
x and y go out of scope at the same time, rather than y leaving scope
before x does.

Program build
-------------

From your top-level directory, doing:

    make bin/c_parser

should create a programme called... `bin/c_parser`.



C90 Declarations
----------------

In C99 (like C++) you are allowed to interleave declarations and statements:

    int f(int i)
    {
        int x=i+5;
        x=x*x;
        int y=x+4;
        return y;
    }

In C90, you must have all declarations before any statements,
so that would need to be re-written as:

    int f(int i)
    {
        int x=i+5;
        int y;
        x=x*x;
        y=x+4;
        return y;
    }

Note that declarations can happen at the start of any scope, so things like:

    int f(int i)
    {
        int x=i+5;
        x=x*x;
        if(1){
            int y=x+4;
            return y;
        }
    }

Thinking about it with your knowledge of parsers and compilers,
you might be able to guess why the older language is more restricted,
while the newer one relaxes it. You also might guess why I
deliberately chose the older syntax for you to implement.

It's worth noting that beyond compiler implementation, there
are many arguments for and against both styles. An argument
for requiring C90 style declarations is that you have
immediate visibility of the total number of variables in a scope.
This gives you a sense of the complexity of a function,
as you can see how many moving parts there are. For example,
Linus Torvalds [likes that aspect](https://lkml.org/lkml/2012/4/12/18),
as the kernel is an extremely large and complex code-base.
There are also rules in the [MISRA-C](https://en.wikipedia.org/wiki/MISRA_C)
guidelines for automotive and embedded software that state
that variables should appear at function scope.

One argument for the newer style is convenience, but also
the idea that that it is better to declare a variable at
the point that it is initialised. A common error in C is
to have a variable which is not initialised on all code
paths:

    {
       int i;

       // Much code

       if(getc()){
           i=1;
       }

       // So codey

       putc(i+1);
    }

Modern compilers will put out a warning about `i` potentially
being used before being initialised, but people may just
ignore that. The move towards more functional and declarative
styles has also encouraged this process - for example, the
`auto` keyword in C++11.
