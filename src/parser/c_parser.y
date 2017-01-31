%code requires{
  #include "tokens.hpp"
  //extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when  generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

%token OR AND NOT LT LE GT GE NE EQ PLUS MINUS TIMES MOD SLASH POWER
%token Keyword Identifier Operator Constant StringLiteral Newline Invalid None
%token INTEGER FLOAT
%token INT VOID UINT
%token WHILE 
%token IF ELSE SWITCH CASE BREAK DEFAULT
%token NUM ID
%token INCLUDE

%type <num> WHILE

%start ROOT

%%

ROOT : WHILE {}

%%

{}
