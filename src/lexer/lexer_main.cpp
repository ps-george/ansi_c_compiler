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
int yylsourcelino = 1;

std::string quote(int i){
  std::string s = std::to_string(i);
  return "\"" + s + "\"";
}

std::string quote(std::string s){
  return "\"" + s + "\"";
}

std::string escape_quotes(std::string s){
  // Replace quotes in original string with \"
  s = std::regex_replace(s,std::regex("\""), "\\\"");
  return s;
}

int main() {
  std::map<std::string, int> sourceline;
  fprintf(stdout, "[\n");
  int p = 0;
  while (1) {
    TokenType type = (TokenType)yylex();
    if (type == Newline) {
      // if newline after preprocessor, no longer interpreting as preprocessor and don't increment sourcelino
      if (p){
        p = 0;
      }
      else {
        yylsourcelino += 1;
      }
      continue;
    }
    // if we come across a # at the beginning of a line, we are intepreting as preprocessor

    if (p){
      if (p==1){
        // source line number, if it's an integer, otherwise... not sure. Should always be integer!
        if (type == Constant){
           yylsourcelino = atoi(yylval.print_text().c_str());
        }
        // if it's not an integer then it is just a #include (except that should be caught by #include!)
      }
      if ((p==2) & (type==StringLiteral)){
        // file name
        yylfile = yylval.print_text();
      }
      else {
        
      }
      p++;
    }
    if (type == Preprocessor) {
      p=1;
      // We don't know the correct file for this line yet
      yylfile = "";      
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
      fprintf(stdout, "\t{}\n");
      break;
    }
    // Replace 
    fprintf(stdout, "\t{\n\t\t\"Class\": %s,\n\t\t\"Text\": %s,\n\t\t\"StreamLine\": %s,\n\t\t\"SourceLine\": %s,\n\t\t\"SourceCol\": %s,\n\t\t\"SourceFile\": %s\n\t},\n",
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
