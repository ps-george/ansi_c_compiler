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

%type <leaf> declaration
%type <raw> STRING ID

%start root
%%

root : declaration { g_root = $1; }


program : func_or_dec { /*$$ = $1*/ }
        | program func_or_dec { }

func_or_dec : function 
            | declaration
 
function : INT ID '(' parameter_list ')' scope { /*$$ = new Function({$4})*/ }
         | INT ID '(' ')' scope

parameter : INT ID { }

parameter_list : parameter {  }
               | parameter_list ',' parameter { }

declaration : INT ID SEMI { $$ = new Variable(*$2); }

scope : '{' '}'

%%

const Leaf *g_root; // Definition of variable (to match declaration earlier)

const Leaf *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
