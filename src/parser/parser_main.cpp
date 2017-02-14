#include "tokens.hpp"
#include "c_parser.tab.h"

#include <iomanip>
#include <string.h>
// Define the instance of the variable that is declared in the header
//YYSTYPE yylval;


// Used for file name
std::string yylfile;

// Used for column number calculations
int len;
int yylcolno = 1;
int yylsourcelino = 1;

// Used for xml print indentation, static member of ast
int Leaf::tabcount = 0;
//int Leaf::changed = 0;

int main() {
  const Leaf *ast=parseAST();
  
  ast->print_xml();
  return 0;
}
