%code requires{
  #include "ast.hpp"
  extern const Node *g_root; // A way of getting the AST out
  
  #include "tokens.hpp"

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
  
  // NOTE: Structure of bison file is fairly well specified, but construction of ast is not.
}

%define parse.error verbose

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
%token '(' ')' '{' '}' '[' ']' ';' ':' ',' '.' ARROW LL RR

%token INCLUDE
// Represents the value associated with any kind of
// AST node.
%union{
  const Node *node;
  const List *list;
  double num;
  std::string *raw;
}

//root : declaration { g_root = new Program({$1}); }
//     | root declaration { g_root = new Program($1->getAllStems(), $2) ; }

%type <node> root program function-definition declaration  parameter delcarator 
%type <list> external-declaration parameter-list declaration-list

%type <node> statement expression-statement compound-statement statement-list iteration-statement selection-statement
%type <node> declaration-seq declaration-list simple-declaration init-declaration
%type <node> expression primary-expression equality-expression
%type <node> var_const

%type <raw> STRING ID CONSTANT

%right ';'

%start root
%%

root : program { g_root = $1; }

program 
  : external-declaration { $$ = new Program({$1}); }
  | program external-declaration { $$ = $$->add($2); }

// EXTERNAL DECLARATIONS
external-declaration
  : function-definition { $$ = $1; }
  | declaration-list ';' { $$ = $1; }
  
// FUNCTION
// Snip the stems from the parameter list to make tree smaller
function-definition 
  : INT ID '(' parameter-list ')' statement { $$ = new Function($2,{$4->add($6)}); } //$4->getAllStems()
  | INT ID '(' ')' statement { $$ = new Function($2,{$5}); }

parameter 
  : INT ID { $$ = new Parameter(*$2); }

parameter-list 
  : parameter { $$ = new ParameterList({$1}); }
  | parameter-list ',' parameter { $$->add($3); }
               
// STATEMENT
statement
  : expression-statement { $$ = $1; }
  | compound-statement { $$ = $1; }
  | iteration-statement { $$ = $1; }
  | selection-statement { $$ = $1; }

selection-statement
  : IF '(' expression ')' statement { $$ = new IfStatement($3, $5); }
  | IF '(' expression ')' statement ELSE statement { $$ = new IfElseStatement($3, $5, $7); }

// COMPOUND STATEMENT
compound-statement
  : '{' '}' { $$ = new Scope({}); }
  | '{' statement-list '}' { $$ = new Scope({$2}); }
  | '{' declaration-seq '}' { $$ = new Scope({$2}); } 
  | '{' declaration-seq statement-list '}' { $$ = new Scope({$2, $3}); }   // declarations must come before statements

statement-list
  : statement { $$ = new List ({$1}); }
  | statement-list statement { $$ = $1->add($2); }

expression-statement
	: ';' { $$ = new List({}); }
  | expression ';' { $$ = $1; }
	//| expression ';'

expression 
  : primary-expression { $$ = $1; }
  
primary-expression
  : equality-expression { $$ = $1; }
  | var_const { $$ = $1; }
  | RETURN ID { $$ = new List({}); }
//  | STRING { $$ = $1; }
  | '(' expression ')' { $$ = $2; }

equality-expression
  : var_const EQ var_const { $$ = new List({}); }

iteration-statement
// Just make scopes with the statement
  : WHILE '(' expression ')' statement { $$ = new WhileIteration({$5}/*$3, $5*/); }
  //| DO statement WHILE '(' expression ')' { $$ = new DoWhileIteration({$2}/*$5, $2*/); }
  | FOR '(' expression-statement expression-statement ')' statement { $$ = new ForIteration({$6}/*$3,$4,$6*/); }
  //| FOR '(' expression-statement expression-statement  ')' { $$ = new ForIteration({}/*$3,$4*/); }

// DECLARATION
declaration-seq
  : declaration-list ';' { $$ = new DeclarationList({$1}); }
  | declaration-seq declaration-list ';' { $$->add($2); }

declaration-list
  : declaration { $$ = new DeclarationList({$1}); }
  | declaration-list ',' declaration { $$->add($3); }

declaration  
  : simple-declaration { $$ = $1; }
  | init-declaration { $$ = $1; }

simple-declaration
  : delcarator { $$ = $1; }

init-declaration
  : delcarator '=' CONSTANT { $$ = $1; }
  | delcarator '=' ID { $$ = $1; }

delcarator : INT ID { $$ = new Variable(*$2); }

var_const
  : ID { $$ = new Variable(*$1); }
  | CONSTANT { $$ = new Constant(*$1); }

%%

const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST() {
  g_root=0;
  yyparse();
  return g_root;
}
