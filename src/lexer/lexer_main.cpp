#include "tokens.hpp"

#include <iomanip>
#include <string.h>

// Define the instance of the variable that is declared in the header
TokenValue yylval;
std::string yylfile;
int yylcolno = 1;

int main() {
  fprintf (stdout, "[\n");
  while (1) {
    TokenType type = (TokenType)yylex();
    if (type == Newline){
      continue;
    }
    if (type == None){
      fprintf (stdout, "{}\n");
      break;
    }
    fprintf (stdout, "{\"Class\" : \"%s\",  Text: \"%s\", \"StreamLine\" %d:,  \"SourceCol\" : %d,  \"SourceFile\" : %s},\n", yylval.Class.c_str(), yylval.Text.c_str(), yylineno, yylcolno, yylfile.c_str());
    yylcolno = yylcolno + yylval.Text.length();
    
  }
  fprintf (stdout, "]\n");
  return 0;
}
