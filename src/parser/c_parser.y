%code requires{
  #include "ast.hpp"

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string string;
}

%token OR AND NOT LT LE GT GE NE EQ PLUS MINUS TIMES MOD SLASH POWER


%token INT VOID UINT
%token WHILE 
%token IF ELSE SWITCH CASE BREAK DEFAULT
%token NUM ID
%token INCLUDE

%start ROOT

%%

ROOT : EXPR { g_root = $1; }

EXPR : TERM                 { $$ = $1; }

TERM : FACTOR               { $$ = $1; }

FACTOR : T_NUMBER           { $$ = new Number( $1 ); }
       | T_LBRACKET EXPR T_RBRACKET { $$ = $2; }

FUNCTION_NAME : T_LOG { $$ = new std::string("log"); }

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
