%code requires{
  #include "ast.hpp"
  extern const Node *g_root; // A way of getting the AST out
  
  #include "tokens.hpp"

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
  
  extern FILE * yyin;
  // NOTE: Structure of bison file is fairly well specified, but construction of ast is not.
}

%define parse.error verbose

// Represents the value associated with any kind of
// AST node.
%union{
  const List *list;
  const Node *node;
  const Function *function;
  const Variable * variable;
  const Statement * statement;
  const Expression *expression;
  const ExpressionStatement *expressionstatement;
  const Type * type;
  const Declaration * declaration;
  const Declarator * declarator;
  double num;
  std::string *raw;
}

%token Invalid
%token ID STRING SIZEOF
%token F_CONSTANT I_CONSTANT C_CONSTANT

%token INT DOUBLE FLOAT CHAR VOID
%token LONG SHORT SIGNED UNSIGNED CONST VOLATILE

%token IF FOR SWITCH CASE DEFAULT DO WHILE BREAK GOTO CONTINUE RETURN 
%token STRUCT ENUM UNION ELLIP
%token EXTERN REGISTER STATIC AUTO TYPEDEF

%token '?' '!' '~' '|' '&' '^' '+' '-' '*' '/' '%'
%type <raw> '?' '!' '~' '|' '&' '^' '+' '-' '*' '/' '%'
%token '=' ADDASS SUBASS MULASS DIVASS MODASS ANDASS ORASS XORASS LLASS RRASS
%type <raw> '=' ADDASS SUBASS MULASS DIVASS MODASS ANDASS ORASS XORASS LLASS RRASS
%token INCR DECR
%type <raw> INCR DECR
%token LE GE EQ NE GT LT LOR LAND
%type <raw> LE GE EQ NE GT LT LOR LAND
%token '(' '{' '}' '[' ']' ';' ':' ',' '.' ARROW LL RR
%type <raw> '(' '{' '}' '[' ']' ';' ':' ',' '.' ARROW LL RR
%nonassoc ')'
%type <raw> ')'
%nonassoc ELSE

%token INCLUDE


//root : declaration { g_root = new Program({$1}); }
//     | root declaration { g_root = new Program($1->getAllStems(), $2) ; }

%type <node> root external-declaration 
%type <node> declarator direct-declarator init-declarator parameter-declaration
%type <type> declaration-specifiers type-specifier storage-class-specifier type-qualifier
%type <declaration> declaration 

%type <function> function-definition

%type <list> identifier-list parameter-list statement-list program declaration-seq init-declarator-list  argument-expression-list

%type <statement> statement compound-statement iteration-statement selection-statement jump-statement labeled-statement 
%type <expressionstatement> expression-statement
%type <expression> expression primary-expression initializer

%type <expression> assignment-expression conditional-expression var_const
%type <expression> LOR-expression LAND-expression OR-expression EOR-expression AND-expression 
%type <expression> relational-expression shift-expression additive-expression multiplicative-expression 
%type <expression> cast-expression prefix-expression postfix-expression equality-expression constant-expression

%type <raw> INT FLOAT STRING ID C_CONSTANT F_CONSTANT I_CONSTANT SIZEOF CHAR
%type <raw> assignment-op

//%right ';'

%start root
%%

root : program { g_root = (const Node *)$1; }

program 
  : external-declaration { $$ = new Program({$1}); }
  | program external-declaration { $$->add($2); }

// EXTERNAL DECLARATIONS
external-declaration
  : function-definition { $$ = $1; }
  | declaration { $$ = $1; }
  
// FUNCTION
// Snip the stems from the parameter list to make tree smaller

function-definition
 	: declaration-specifiers declarator compound-statement { $$ = new Function($1, $2, $3); }
//  | declaration-specifiers declarator declaration-seq compound-statement { $$ = new Function($2, $3, $4); } weird old-style function
 	

parameter-list 
  : parameter-declaration { $$ = new ParameterList({$1}); }
	| parameter-list ',' parameter-declaration { $$->add($3);  }

parameter-declaration
	: declaration-specifiers declarator { $$ = new Declaration($1, new DeclarationList({$2})); }
  	//| declaration_specifiers abstract_declarator
  	//| declaration_specifiers
  	
               
// STATEMENT
statement
  : labeled-statement { $$ =$1; }
  | compound-statement { $$ = $1; }
  | expression-statement { $$ = $1; }
  | selection-statement { $$ = $1; }
  | iteration-statement { $$ = $1; }
  | jump-statement { $$ = $1; }

labeled-statement
  : ID ':' statement { $$ = new LabeledStatement($1, $3); }
	| CASE constant-expression ':' statement { $$ = new CaseLabel($2, $4); }
	| DEFAULT ':' statement { $$ = new DefaultLabel($3); }
  
jump-statement
  : GOTO ID ';' { $$ = new GotoStatement(*$2); } 
  | CONTINUE ';' {$$ = new ContinueStatement(); }
  | BREAK ';' { $$ = new BreakStatement(); }
  | RETURN expression-statement { $$ = new ReturnStatement($2); }

selection-statement
  : IF '(' expression ')' statement { $$ = new IfElseStatement($3, $5, new CompoundStatement()); }
  // SHIFT/REDUCE CONFLICT
  | IF '(' expression ')' statement ELSE statement { $$ = new IfElseStatement($3, $5, $7); } 
  | SWITCH '(' expression ')' statement { $$ = new SwitchStatement($3, $5); }

// COMPOUND STATEMENT
compound-statement
  : '{' '}' { $$ = new CompoundStatement(); }
  | '{' statement-list '}' { $$ = new CompoundStatement(new List({}), $2); }
  | '{' declaration-seq '}' { $$ = new CompoundStatement($2,new List({})); } 
  | '{' declaration-seq statement-list '}' { $$ = new CompoundStatement($2, $3); }   // declarations must come before statements

statement-list
  : statement { $$ = new List({$1}); }
  | statement-list statement { $$->add($2); }

/*
    EXPRESSIONS
 */

expression-statement
	: ';' { $$ = new ExpressionStatement(new EmptyExpression()); }
  | expression ';' { $$ = new ExpressionStatement($1); }

expression 
  : assignment-expression { $$ = new ExpressionList({$1}); }
  | expression ',' assignment-expression { $$->add($3); }
  
assignment-expression
  : conditional-expression { $$ = $1; }
  | prefix-expression assignment-op assignment-expression { $$ = new AssignmentExpression($1, $3, $2); }

conditional-expression
  : LOR-expression { $$ = $1; }
  | LOR-expression '?' expression ':' conditional-expression { $$ = new TrinaryExpression($1, $3, $5); }

LOR-expression
  : LAND-expression { $$ = $1; }
  | LOR-expression LOR LAND-expression { $$ = new BinaryExpression($1, $3, $2); }

LAND-expression
  : OR-expression { $$ = $1; }
  | LAND-expression LAND OR-expression { $$ = new BinaryExpression($1, $3, $2); }

OR-expression
  : EOR-expression { $$ = $1; }
  | OR-expression '|' EOR-expression { $$ = new BinaryExpression($1, $3, $2); }

EOR-expression
  : AND-expression { $$ = $1; }
  | EOR-expression '^' AND-expression { $$ = new BinaryExpression($1, $3, $2); }

AND-expression
  : equality-expression { $$ = $1; }
  | AND-expression '&' equality-expression { $$ = new BinaryExpression($1, $3, $2); }
  
equality-expression 
  : relational-expression { $$ = $1; }
  | equality-expression EQ relational-expression { $$ = new BinaryExpression($1, $3, $2); }
  | equality-expression NE relational-expression { $$ = new BinaryExpression($1, $3, $2); }
  
relational-expression
  : shift-expression
  | relational-expression LT shift-expression { $$ = new BinaryExpression($1, $3, $2); }
  | relational-expression GT shift-expression { $$ = new BinaryExpression($1, $3, $2); }
  | relational-expression LE shift-expression { $$ = new BinaryExpression($1, $3, $2); }
  | relational-expression GE shift-expression { $$ = new BinaryExpression($1, $3, $2); }

shift-expression
  : additive-expression { $$ = $1; }
  | shift-expression LL additive-expression { $$ = new BinaryExpression($1, $3, $2); }
  | shift-expression RR additive-expression { $$ = new BinaryExpression($1, $3, $2); }

additive-expression
  : multiplicative-expression { $$ = $1; }
  | additive-expression '+' multiplicative-expression { $$ = new BinaryExpression($1, $3, $2); }
  | additive-expression '-' multiplicative-expression { $$ = new BinaryExpression($1, $3, $2); }

multiplicative-expression
  : cast-expression { $$ = $1; }
  | multiplicative-expression '*' cast-expression { $$ = new BinaryExpression($1, $3, $2); }
  | multiplicative-expression '/' cast-expression { $$ = new BinaryExpression($1, $3, $2); }
  | multiplicative-expression '%' cast-expression { $$ = new BinaryExpression($1, $3, $2); }

cast-expression
  : prefix-expression { $$ = $1; }
//  | '(' type-name ')' cast-expression { $$ = new CastExpression($2,$4); }

prefix-expression
  : postfix-expression { $$ = $1; }
  | INCR prefix-expression { $$ = new PrefixExpression($2, $1); }
  | DECR prefix-expression { $$ = new PrefixExpression($2, $1); }
  // | unary-operator cast-expression { $$ = new PrefixExpression(); }
  | SIZEOF prefix-expression { $$ = new PrefixExpression($2, $1); }

postfix-expression
  : primary-expression { $$ = $1; }
  | postfix-expression '[' expression ']' { $$ = new SquareOperator($1, $3); }
  | postfix-expression '(' ')' { $$ = new FunctionCall($1); }
  | postfix-expression '(' argument-expression-list ')' { $$ = new FunctionCall($1, $3); }
  | postfix-expression '.' ID { $$ = new DotOperator($1, $3); }
  | postfix-expression ARROW ID { $$ = new ArrowOperator($1, $3); }
  | postfix-expression INCR { $$ = new PostfixExpression($1, $2); }
  | postfix-expression DECR { $$ = new PostfixExpression($1, $2); }

argument-expression-list
  : assignment-expression { $$ = new ExpressionList({$1}); }
  | argument-expression-list ',' assignment-expression { $$->add($3); }

primary-expression
  : var_const { $$ = $1; }
  | STRING { $$ = new StringLiteral(*$1); }
  | '(' expression ')' { $$ = $2; }

constant-expression
  : conditional-expression { $$ = $1; }

assignment-op
  : '=' { $$ = $1; }
  | MULASS  { $$ = $1; }
  | DIVASS { $$ = $1; }
  | MODASS { $$ = $1; }
  | ADDASS { $$ = $1; }
  | SUBASS { $$ = $1; }
  | LLASS { $$ = $1; }
  | RRASS { $$ = $1; }
  | ANDASS { $$ = $1; }
  | XORASS { $$ = $1; }
  | ORASS { $$ = $1; }
  

/* END OF EXPRESSIONS */

iteration-statement
// Just make scopes with the statement
  : WHILE '(' expression ')' statement { $$ = new WhileStatement($3, $5); }
  | DO statement WHILE '(' expression ')' { $$ = new DoWhileStatement($2, $5); }
  | FOR '(' expression-statement expression-statement expression ')' statement { $$ = new EEEForStatement($3, $4, $5, $7); }
  | FOR '(' expression-statement expression-statement  ')' statement { $$ = new EEForStatement($3, $4, $6); }
  | FOR '(' declaration expression-statement ')' statement { $$ = new DEForStatement($3, $4, $6); }
	| FOR '(' declaration expression-statement expression ')' statement { $$ = new DEEForStatement($3,$4,$5,$7); }

// DECLARATION
declaration-seq 
  : declaration { $$ = new DeclarationList({$1}); }
  | declaration-seq declaration { $$->add($2); }

declaration
  : declaration-specifiers ';' { $$ = new Declaration($1, new List({})); }
  | declaration-specifiers init-declarator-list ';' { $$ = new Declaration($1,$2); }

declaration-specifiers
  : storage-class-specifier { $$ = $1; }
	| storage-class-specifier declaration-specifiers { $2->add($1); $$ = $2; }
	| type-specifier { $$ = $1; }
	| type-specifier declaration-specifiers { $2->add($1); $$ = $2; }
	| type-qualifier { $$ = $1; }
	| type-qualifier declaration-specifiers { $2->add($1); $$ = $2; }

//  : type-specifier { $$ = $1;}
//  | type-specifier '*' {$1->setPtr(); $$ = $1; }

init-declarator-list
	: init-declarator { $$ = new DeclarationList({$1}); }
	| init-declarator-list ',' init-declarator { $$->add($3); }

type-specifier
  : VOID { $$ = new Type(Void); }
	| CHAR { $$ = new Type(Char); }
	| INT { $$ = new Type(Int); }
	| SHORT { $$ = new Type(Short); }
	| LONG { $$ = new Type(Long); }
	| FLOAT { $$ = new Type(Float); }
	| DOUBLE { $$ = new Type(Double); }
	| SIGNED { $$ = new Type(Signed); }
	| UNSIGNED { $$ = new Type(Unsigned); }

type-qualifier
	: CONST { $$ = new Type(Const); }
	| VOLATILE { $$ = new Type(Volatile); }

storage-class-specifier
	: TYPEDEF { $$ = new Type(Typedef); }
//	| EXTERN
//	| STATIC
//	| AUTO
//	| REGISTER

init-declarator
	: declarator { $$ = $1; }
	| declarator '=' initializer { $$ = new InitDeclarator($1,$3); }

initializer
  : assignment-expression { $$ = $1; }
  
declarator
  : direct-declarator { $$ = $1; }

direct-declarator 
  : 
   '(' declarator ')' { $$ = $2; } // declarator can be surrounded by any number of brackets 
  | direct-declarator '[' constant-expression ']' { $$ = new ArrayDeclarator($1, $3); } // Array with fixed size
  | direct-declarator '[' ']' { $$ = new ArrayDeclarator($1, new Constant("-1")); }   // Array without size specified
  | direct-declarator '(' ')' { $$ = new FunctionDeclarator($1, new List({})); }                // Function with no arguments
  | direct-declarator '(' parameter-list ')' { $$ = new FunctionDeclarator($1,$3); } // Function declaration with parameter list
  | direct-declarator '(' identifier-list ')' { $$ = new FunctionDeclarator($1,$3); } // Function declaration with id list, must be followed by weird declaration list following definition
  | ID { $$ = new Variable($1); }
                                              // e.g. int max(a,b) int a,b; {}


var_const
  : ID { $$ = new Variable($1); }
  | I_CONSTANT { $$ = new IntConstant(*$1); }
  | F_CONSTANT { $$ = new FloatConstant(*$1); }
  | C_CONSTANT { $$ = new CharConstant(*$1); }

identifier-list
	: ID { $$ = new List({new Variable($1)}); }
	| identifier-list ',' ID { $$->add(new Variable($3)); }

%%

const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST() {
  g_root=0;
  yyparse();
  return g_root;
}
