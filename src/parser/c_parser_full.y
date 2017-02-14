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

root : statement
     | root statement

unary_op : '&'
	       | '*'
         | '+'
         | '-'
         | '~'
         | '!'

assign_op : '='
                    | MULASS
                    | DIVASS
                    | MODASS
                    | ADDASS
                    | SUBASS
                    | LLASS
                    | RRASS
                    | ANDASS
                    | XORASS
                    | ORASS
                    ;

statement : primary_expr ';'
         | ';'
        

primary_expr : ID
	           | CONSTANT
             | STRING
             | '(' expr ')'

expr : assign_expr
     | expr ',' assign_expr

assign_expr : cond_expr
            | unary_expr assign_op assign_expr

cond_expr : logical_expr
          | logical_expr '?' expr ':' cond_expr

logical_expr : bit_expr
             | logical_expr LOR bit_expr
             | logical_expr LAND bit_expr

bit_expr : comp_expr
         | bit_expr '|'  comp_expr
         | bit_expr '^' comp_expr
         | bit_expr '&' comp_expr

comp_expr : shift_expr
          | comp_expr EQ shift_expr
          | comp_expr NE shift_expr
          | comp_expr '<' shift_expr
          | comp_expr '>' shift_expr
          | comp_expr LE shift_expr
          | comp_expr GE shift_expr

shift_expr : add_expr
           | shift_expr LL add_expr
           | shift_expr RR add_expr

add_expr : mult_expr
         | add_expr '+' mult_expr
         | add_expr '-' mult_expr

mult_expr : cast_expr
          | mult_expr '*' cast_expr
          | mult_expr '/' cast_expr
          | mult_expr '%' cast_expr


cast_expr : unary_expr
	        | '(' base_type ')' cast_expr

base_type : VOID
          | CHAR
          | SHORT
          | INT
          | LONG
          | FLOAT
          | DOUBLE
          | SIGNED
          | UNSIGNED
	;

unary_expr : postfix_expr
	         | INCR unary_expr
           | DECR unary_expr
           | unary_op cast_expr


postfix_expr : primary_expr
             | postfix_expr '[' expr ']'
             | postfix_expr '(' ')' {/*| postfix_expr '(' argument_expr_list ')'*/  }
             | postfix_expr '.' ID
             | postfix_expr ARROW ID
             | postfix_expr INCR
             | postfix_expr DECR
;




%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
