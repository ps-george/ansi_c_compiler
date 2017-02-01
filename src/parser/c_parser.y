%code requires{
  #include "tokens.hpp"
  //extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when  generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

%token Invalid
%token ID STRING SIZEOF
%token CONSTANT

%token INT DOUBLE FLOAT CHAR VOID
%token LONG SHORT SIGNED UNSIGNED CONST VOLATILE

%token IF ELSE FOR SWITCH CASE DEFAULT DO WHILE BREAK GOTO CONTINUE RETURN 
%token STRUCT ENUM UNION ELLIP
%token EXTERN REGISTER STATIC AUTO TYPEDEF

%token ORASS XORASS MULASS DIVASS MODASS ADDASS SUBASS LLASS RRASS ANDASS
%token INCR DECR
%token ASGN LE GE EQ NE GT LT LOR LAND NOT Q BNOT BOR BAND BXOR PLUS SUB TIMES DIV MOD
%token PLEFT PRIGHT CPLEFT CPRIGHT SPLEFT SPRIGHT SEMI COLON COMMA DOT ARROW LL RR BSLASH

%token INCLUDE

%type <string> STRING

%start ROOT

%%

ROOT : PRIMARY_EXPR;

EXPR : {};

PRIMARY_EXPR : ID | CONSTANT | STRING | PLEFT EXPR PRIGHT ;




%%

{}
