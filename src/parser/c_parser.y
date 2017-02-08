%code requires{
  #include "ast.hpp"
  extern const Expression *g_root; // A way of getting the AST out
  
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

%type <string> STRING

%start root
%%

primary-expression
	: ID
	| CONSTANT
	| STRING
	| '(' expression ')'
	;

postfix-expression
	: primary-expression
	| postfix-expression '[' expression ']'
	| postfix-expression '(' ')'
	| postfix-expression '(' argument-expression-list ')'
	| postfix-expression '.' ID
	| postfix-expression ARROW ID
	| postfix-expression INCR
	| postfix-expression DECR
	;

argument-expression-list
	: assignment-expression
	| argument-expression-list ',' assignment-expression
	;

unary-expression
	: postfix-expression
	| INCR unary-expression
	| DECR unary-expression
	| unary-operator cast-expression
	| SIZEOF unary-expression
	| SIZEOF '(' type-name ')'
	;

unary-operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast-expression
	: unary-expression
	| '(' type-name ')' cast-expression
	;


%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
