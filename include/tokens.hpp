#ifndef tokens_hpp
#define tokens_hpp

#include <string>

enum TokenType {
  None = 0,    // This indicates there are no more tokens
  Keyword = 1, // token codes must be positive
  Identifier,
  Operator,
  Constant,
  StringLiteral,
  Newline,
  Preprocessor,
  PreprocessorFile,
  Invalid,
  FLOAT,
  INTEGER,
  BNOT,
  BOR,
  BAND,
  NOT,
  LOR,
  LAND,
  LT,
  LE,
  GT,
  GE,
  NE,
  EQ,
  PLUS,
  MINUS,
  TIMES,
  MOD,
  DIV,
  BXOR,
  ASGN,
  SEMI,
  COMMA,
  BSLASH,
  PLEFT,
  PRIGHT,
  CPLEFT,
  CPRIGHT,
  SPLEFT,
  SPRIGHT,
  ARROW,
  DOT,
  LL,
  RR
};

struct TokenValue {
  int num;
  std::string raw;
};

// This is a global variable used to move the
// attribute value from the lexer back to the
// main program.
// By convention it is called yylval, as that is
// the name that will be automatially generated
// by Bison (see next lab).
extern TokenValue yylval;
extern int yylineno;
extern int yylcolno;
extern int yylsourcelino;
extern std::string yylfile;
// This is the lexer function defined by flex. Each
// time it is called, a token type value will be
// returned.
extern int yylex();

#endif
