#include "tokens.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <string.h>
// Define the instance of the variable that is declared in the header
TokenValue yylval;
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
  s = std::regex_replace(s,std::regex("\""), "\\\"");
  return s;
}

std::string classname(TokenType t){
  switch(t){
    case Keyword: return "Keyword";
    case Identifier: return "Identifier";
    case Operator: return "Operator";
    case Constant: return "Constant";
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
    TokenType type = (TokenType)yylex();
    Class = classname(type);
    
    if (type == None) {
      // finish
      fprintf(stdout, "\t{}\n");
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
  fprintf(stdout, "]\n");
  return 0;
}
