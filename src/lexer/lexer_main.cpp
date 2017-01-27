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
  // Replace quotes in original string with \"
  return "\"" + s + "\"";
}

std::string escape_quotes(std::string s){
  s = std::regex_replace(s,std::regex("\""), "\\\"");
  return s;
}

int main() {
  std::map<std::string, int> sourceline;
  fprintf(stdout, "[\n");

  while (1) {
    TokenType type = (TokenType)yylex();
    if (type == Newline) {
      if (!((yylval.Class == "Preprocessor") |
            (yylval.Class == "PreprocFile"))) {
        yylsourcelino += 1;
      }
      continue;
    }
    if (type == Preprocessor) {
      // continue;
    }
    if (type == PreprocessorFile) {
      std::regex_search(yylval.Text.c_str(), cm, std::regex("\\b[0-9]+\\b"),
                        std::regex_constants::match_default);
      sourceline[yylfile] = atoi(((std::string)cm[0]).c_str());
      yylsourcelino = sourceline[yylfile];
    }
    if (type == Invalid) {
      int y;
      std::cin >> y;
    }
    if (type == None) {
      fprintf(stdout, "{}\n");
      break;
    }
    // Replace 
    fprintf(stdout, "{ \"Class\" : %-15s, \"Text\" : %-20s, \"StreamLine\" : %7s, \"SourceLine\" : %6s, \"SourceCol\" : %4s, \"SourceFile\" : %s },\n",
            quote(yylval.print_class()).c_str(),
            quote(escape_quotes(yylval.print_text())).c_str(),
            quote(yylineno).c_str(),
            quote(yylsourcelino).c_str(),
            quote(yylcolno).c_str(),
            quote(yylfile).c_str());
    yylcolno += yylval.Text.length();
  }
  fprintf(stdout, "]\n");
  return 0;
}
