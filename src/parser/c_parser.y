%code requires{
  #include "tokens.hpp"
  //extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when  generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

%token Keyword Identifier Operator Constant StringLiteral Newline Invalid None
%token AUTO BREAK DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF CASE CHAR CONST CONTINUE DEFAULT DO INT LONG STRUCT SWITCH REGISTER TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE RETURN SHORT SIGNED SIZEOF STATIC

%token ASGN LE GE EQ NE GT LT LOR LAND BOR BAND BXOR PLUS MINUS TIMES DIV BNOT NOT
%token PLEFT PRIGHT CPLEFT CPRIGHT SPLEFT SPRIGHT SEMI COMMA DOT ARROW LL RR BSLASH

%token INCLUDE

%type <string> StringLiteral

%start ROOT

%%

ROOT : WHILE {}

%%

{}
