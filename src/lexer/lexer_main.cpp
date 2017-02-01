#include "tokens.hpp"
#include "c_parser.tab.h"

#include <iomanip>
#include <regex>
#include <string.h>
// Define the instance of the variable that is declared in the header
YYSTYPE yylval;
std::string yylfile;
std::string t;
std::cmatch cm;
int yylcolno = 1;
int yylsourcelino = 0;

std::string quote(int i){
  std::string s = std::to_string(i);
  return "\"" + s + "\"";
}

std::string quote(std::string s){
  return "\"" + s + "\"";
}

std::string escape_chars(std::string s){
  // Replace quotes in original string with \"
  // replace backslash with double
  //s = std::regex_replace(s,std::regex("/\\/"), "\\\\");
  // replace all backslash with double backslash, unless there is a quote afterward, n, t
  //s = std::regex_replace(s,std::regex("[(\\)]^([nt\"])"), "\\\\");
  
  // replace all quotes with \" unless they are already.
  s = std::regex_replace(s,std::regex("[^(\\)]\""), "\\\"");
  return s;
}

std::string classname(yytokentype t){
  if (t>297 && t<329){
    return "Operator";
  }
  switch(t){
  /* KEYWORDS */
    case AUTO:
    case BREAK:
    case DOUBLE:
    case ELSE:
    case ENUM:
    case EXTERN:
    case FLOAT:
    case FOR:
    case GOTO:
    case IF:
    case CASE:
    case CHAR:
    case CONST:
    case CONTINUE:
    case DEFAULT:
    case DO:
    case INT:
    case LONG:
    case STRUCT:
    case SWITCH:
    case REGISTER:
    case TYPEDEF:
    case UNION:
    case UNSIGNED:
    case VOID:
    case VOLATILE:
    case WHILE:
    case RETURN:
    case SHORT:
    case SIGNED:
    case SIZEOF:
    case STATIC: return "Keyword";
    /* Identifiers */
    case ID: return "Identifier";
     /* Operators */
    case ASGN:
    case LE:
    case GE:
    case EQ:
    case NE:
    case GT:
    case LT:
    case LOR:
    case LAND:
    case BOR:
    case BAND:
    case BXOR:
    case PLUS:
    case MINUS:
    case TIMES:
    case DIV:
    case PLEFT:
    case PRIGHT:
    case CPLEFT:
    case CPRIGHT:
    case SPLEFT:
    case SPRIGHT:
    case SEMI:
    case COMMA:
    case DOT:
    case ARROW:
    case LL:
    case RR:
    case BNOT:
    case NOT:
    case BSLASH: return "Operator";
    /* Constants */
    case FLOATC:
    case INTC: return "Constant";
    /* StringLiterals */
    case STRING: return "StringLiteral";
    //  Unncessary
    // case NEWLINE: return "Newline";
    default: fprintf(stderr, "Invalid: %s, StreamLine: %s, ColNum: %s\n", yylval.raw.c_str(), quote(yylineno).c_str(), quote(yylcolno).c_str() ); return "Invalid";
  }
}
int main() {
  fprintf(stdout, "[\n");
  std::string Class;
  while (1) {
    yytokentype type = (yytokentype)yylex();
    if (!type) {
      break;
    }
    Class = classname(type);
    // Replace 
    fprintf(stdout, "\t{\n\t\t\"Class\": %s,\n\t\t\"Text\": %s,\n\t\t\"StreamLine\": %s,\n\t\t\"SourceLine\": %s,\n\t\t\"SourceCol\": %s,\n\t\t\"SourceFile\": %s\n\t},\n",
            quote(Class).c_str(),
            quote(escape_chars(yylval.raw)).c_str(),
            quote(yylineno).c_str(),
            quote(yylsourcelino).c_str(),
            quote(yylcolno).c_str(),
            quote(yylfile).c_str());
    yylcolno += yylval.raw.length();
  }
  fprintf(stdout, "\t{}\n]\n");
  return 0;
}
