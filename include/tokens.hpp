#ifndef tokens_hpp
#define tokens_hpp

#include <string>
//#include "ast.hpp"

/*
struct YYSTYPE {
  double num;
  std::string raw;
  int len;
};
*/
// This is a global variable used to move the
// attribute value from the lexer back to the
// main program.
// By convention it is called yylval, as that is
// the name that will be automatially generated
// by Bison (see next lab).
//extern YYSTYPE yylval;

extern int len;
extern int yylineno;
extern int yylcolno;
extern int yylsourcelino;
extern std::string yylfile;
// This is the lexer function defined by flex. Each
// time it is called, a token type value will be
// returned.
extern int yylex();

#endif
