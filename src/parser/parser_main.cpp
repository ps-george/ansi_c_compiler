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
int Node::tabcount = 0;
//int Node::changed = 0;

int main(int argc, char * argv[]) {
  
  const Node *ast=parseAST();
  if (argc>1){
    std::string arg(argv[1]);
    if (arg=="c"){
      ast->print_c();
    }
  }
  else {
    fprintf(stdout,"<?xml version=\"1.0\"?>\n");
    ast->print_xml();
  }
  return 0;
}
