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

%type <leaf> declaration root function parameter_list parameter func_or_dec variable program
%type <raw> STRING ID

%start root
%%

root : program { g_root = $1; }

// FUNCTION OR DECLARATION
     
program : func_or_dec { $$ = new Program({$1}); }
        | program func_or_dec { $$ = $$->add($2); }

// FUNCTION OR DECLARATION
func_or_dec : function { $$ = $1; }
            | declaration { $$ = $1; }
 
// FUNCTION
// Snip the stems from the parameter list
function : INT ID '(' parameter_list ')' SEMI { $$ = new Function($2,$4->getAllStems()); }
         | INT ID '(' ')' SEMI { $$ = new Function($2,{}); }

parameter : INT ID { $$ = new Parameter(*$2); }

parameter_list : parameter { $$ = new Branch({$1}); }
               | parameter_list ',' parameter { $$->add($3); }

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
