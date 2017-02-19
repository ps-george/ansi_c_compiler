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
  const List *list;
  const Node *node;
  double num;
  std::string *raw;
}

//root : declaration { g_root = new Program({$1}); }
//     | root declaration { g_root = new Program($1->getAllStems(), $2) ; }

%type <node> root function-definition declaration parameter delcarator 
%type <node> external-declaration parameter-list declaration-list statement-list program

%type <node> statement expression-statement compound-statement iteration-statement selection-statement
%type <node> declaration-seq simple-declaration init-declaration
%type <node> expression primary-expression assignment-expression conditional-expression 
%type <node> LOR-expression LAND-expression OR-expression EOR-expression AND-expression 
%type <node> relational-expression shift-expression additive-expression multiplicative-expression 
%type <node> cast-expression prefix-expression postfix-expression equality-expression

%type <node> var_const

%type <raw> STRING ID CONSTANT

%right ';'

%start root
%%

root : program { g_root = (const Node*)$1; }

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
  : INT ID '(' parameter-list ')' statement { $$ = new Function($2, $4, $6); } //$4->getAllStems()
  | INT ID '(' ')' statement { $$ = new Function($2, new ParameterList({}),$5 ); }

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
  : '{' '}' { $$ = new CompoundStatement(new List({}), new List({})); }
  | '{' statement-list '}' { $$ = new CompoundStatement(new List({}), new List({$2})); }
  | '{' declaration-seq '}' { $$ = new CompoundStatement(new List({$2}),new List({})); } 
  | '{' declaration-seq statement-list '}' { $$ = new CompoundStatement(new List({$2}), new List({$3})); }   // declarations must come before statements

statement-list
  : statement { $$ = new List ({$1}); }
  | statement-list statement { $$ = $1->add($2); }

// Expressions
expression-statement
	: ';' { $$ = new List({}); }
  | expression ';' { $$ = $1; }
	//| expression ';'

expression 
  : assignment-expression { $$ = new ExpressionList({$1}); }
  | expression ',' assignment-expression { $$ = $$->add($3); }
  
assignment-expression
  : conditional-expression { $$ = $1; }
  | prefix-expression '=' assignment-expression { $$ = new AssignmentExpression($1, $3); }

conditional-expression
  : LOR-expression { $$ = $1; }
  | LOR-expression '?' expression ':' conditional-expression { $$ = new TrinaryExpression($1, $3, $5); }

LOR-expression
  : LAND-expression { $$ = $1; }
  | LOR-expression LOR LAND-expression { $$ = new LORExpression($1, $3); }

LAND-expression
  : OR-expression { $$ = $1; }
  | LAND-expression LAND OR-expression { $$ = new ANDExpression($1, $3); }

OR-expression
  : EOR-expression { $$ = $1; }
  | OR-expression '|' EOR-expression { $$ = new ORExpression($1, $3); }

EOR-expression
  : AND-expression { $$ = $1; }
  | EOR-expression '^' AND-expression { $$ = new EORExpression($1, $3); }

AND-expression
  : equality-expression { $$ = $1; }
  | AND-expression '&' equality-expression { $$ = new ANDExpression($1, $3); }
  
equality-expression 
  : relational-expression { $$ = $1; }
  | equality-expression EQ relational-expression { $$ = new EQExpression($1, $3); }
  | equality-expression NE relational-expression { $$ = new NEExpression($1, $3); }
  
relational-expression
  : shift-expression
  | relational-expression '<' shift-expression { $$ = new LTExpression($1, $3); }
  | relational-expression '>' shift-expression { $$ = new GTExpression($1, $3); }
  | relational-expression LE shift-expression { $$ = new LEExpression($1, $3); }
  | relational-expression GE shift-expression { $$ = new GEExpression($1, $3); }

shift-expression
  : additive-expression { $$ = $1; }
  | shift-expression LL additive-expression { $$ = new LLExpression($1, $3); }
  | shift-expression RR additive-expression { $$ = new RRExpression($1, $3); }

additive-expression
  : multiplicative-expression { $$ = $1; }
  | additive-expression '+' multiplicative-expression { $$ = new AddExpression($1,$3); }
  | additive-expression '-' multiplicative-expression { $$ = new SubExpression($1,$3); }

multiplicative-expression
  : cast-expression { $$ = $1; }
  | multiplicative-expression '*' cast-expression { $$ = new MulExpression($1, $3); }
  | multiplicative-expression '/' cast-expression { $$ = new DivExpression($1, $3); }
  | multiplicative-expression '%' cast-expression { $$ = new ModExpression($1, $3); }

cast-expression
  : prefix-expression { $$ = $1; }
//  | '(' type-name ')' cast-expression { $$ = new CastExpression($2,$4); }

prefix-expression
  : postfix-expression { $$ = $1; }
  | INCR prefix-expression { $$ = new PreIncrExpression($2); }
  | DECR prefix-expression { $$ = new PreDecrExpression($2); }
  // | unary-operator cast-expression { $$ = new PrefixExpression(); }
  | SIZEOF prefix-expression { $$ = new SizeofExpression($2); }

postfix-expression
  : primary-expression { $$ = $1; }
  | postfix-expression '[' expression ']' { $$ = new PostfixExpression($1); }
//  | postfix-expression '(' argument-expression-list ')' { $$ = new PostfixExpression($1); }
  | postfix-expression '.' ID { $$ = new PostfixExpression($1); }
  | postfix-expression ARROW ID { $$ = new PostfixExpression($1); }
  | postfix-expression INCR { $$ = new PostIncrExpression($1); }
  | postfix-expression DECR { $$ = new PostDecrExpression($1); }

primary-expression
  : equality-expression { $$ = $1; }
  | var_const { $$ = $1; }
  | RETURN ID { $$ = new List({}); }
  | STRING { $$ = new StringLiteral(*$1); }
  | '(' expression ')' { $$ = $2; }

equality-expression
  : var_const EQ var_const { $$ = new List({}); }

iteration-statement
// Just make scopes with the statement
  : WHILE '(' expression ')' statement { $$ = new WhileStatement($3, $5); }
  //| DO statement WHILE '(' expression ')' { $$ = new DoWhileStatement({$2}/*$5, $2*/); }
  | FOR '(' expression-statement expression-statement expression-statement ')' statement { $$ = new ForStatement($3, $4, $5, $7); }
  //| FOR '(' expression-statement expression-statement  ')' { $$ = new ForStatement({}/*$3,$4*/); }

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
