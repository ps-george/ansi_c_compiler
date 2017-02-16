%code requires{
  #include "ast.hpp"
  extern const Leaf *g_root; // A way of getting the AST out
  
  #include "tokens.hpp"

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
  
  // NOTE: Structure of bison file is fairly well specified, but construction of ast is not.
}

%token Invalid
%token ID STRING SIZEOF
%token CONSTANT

%token INT DOUBLE FLOAT CHAR VOID
%token LONG SHORT SIGNED UNSIGNED CONST VOLATILE

%token IF ELSE FOR SWITCH CASE DEFAULT DO WHILE BREAK GOTO CONTINUE RETURN 
%token STRUCT ENUM UNION ELLIP
%token EXTERN REGISTER STATIC AUTO TYPEDEF

%token '?' '!' '~' '|' '&' '^' '+' '-' '*' '/' '%'
%token '=' ADDASS SUBASS MULASS DIVASS MODASS ANDASS ORASS XORASS LLASS RRASS
%token INCR DECR
%token LE GE EQ NE GT LT LOR LAND
%token '(' ')' '{' '}' '[' ']' SEMI COLON ',' '.' ARROW LL RR

%token INCLUDE

// Represents the value associated with any kind of
// AST node.
%union{
  const Leaf *leaf;
  double num;
  std::string *raw;
}

//root : declaration { g_root = new Program({$1}); }
//     | root declaration { g_root = new Program($1->getAllStems(), $2) ; }

%type <leaf> root program external-declaration function-definition declaration parameter-list parameter variable 
%type <raw> STRING ID

%start root
%%

root : program { g_root = $1; }

program 
  : external-declaration { $$ = new Program({$1}); }
  | program external-declaration { $$ = $$->add($2); }

// EXTERNAL DECLARATIONS
external-declaration
  : function-definition { $$ = $1; }
  | declaration { $$ = $1; }

// FUNCTION
// Snip the stems from the parameter list
function-definition 
  : INT ID '(' parameter-list ')' compound-statement { $$ = new Function($2,$4->getAllStems()); }
  | INT ID '(' ')' compound-statement { $$ = new Function($2,{}); }

parameter 
  : INT ID { $$ = new Parameter(*$2); }

parameter-list 
  : parameter { $$ = new Branch({$1}); }
  | parameter-list ',' parameter { $$->add($3); }
               
// COMPOUND STATEMENT
compound-statement
  : SEMI { }

// DECLARATION
declaration : variable SEMI { $$ = $1; }

variable : INT ID { $$ = new Variable(*$2); };

scope : '{' '}'

%%

const Leaf *g_root; // Definition of variable (to match declaration earlier)

const Leaf *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
