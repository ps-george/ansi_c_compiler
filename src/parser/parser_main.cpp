#include "tokens.hpp"
#include "c_parser.tab.h"

#include <iomanip>
#include <string.h>
// Define the instance of the variable that is declared in the header
//YYSTYPE yylval;
std::string yylfile;
std::string t;
int yylcolno = 1;
int yylsourcelino = 1;

int Leaf::tabcount = 0;
//int Leaf::changed = 0;

int main() {
  
  
  const Leaf *ast=parseAST();
  
  ast->print_xml();
  return 0;
}
