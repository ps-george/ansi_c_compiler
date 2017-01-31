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
  if (t>11 && t<45){
    return "Operator";
  }
  switch(t){
  /* KEYWORDS */
  /*
    case: CASE
    case: DEFAULT
    case: IF 
    case: ELSE 
    case: SWITCH 
    case: WHILE 
    case: DO 
    case: FOR 
    case: GOTO 
    case: CONTINUE 
    case: BREAK 
    case: RETURN */
    case Keyword: return "Keyword";
    /* Identifiers */
    case Identifier: return "Identifier";
    /* Operators */
    case Operator: return "Operator";
    /* Constants */
    case FLOAT:
    case INTEGER:    
    case Constant: return "Constant";
    /* StringLiterals */
    case StringLiteral: return "StringLiteral";
    case Newline: return "Newline";
    case Invalid: return "Invalid";
    default: return "Error";
  }
}
int main() {
  fprintf(stdout, "[\n");
  std::string Class;
  while (1) {
    yytokentype type = (yytokentype)yylex();
    Class = classname(type);
    
    if (type == None) {
      // finish
      
      break;
    }
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
