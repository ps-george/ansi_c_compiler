#include "tokens.hpp"
#include "c_parser.tab.h"
#include "codegen_helpers.hpp"

#include <iomanip>
#include <string.h>
#include <iostream>

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
bool Node::parser = 0;
//int Node::changed = 0;

int main(int argc, char * argv[]) {
  // Parse the input into the AST
  const Node *ast=parseAST();
  //ast->print_xml();
  // Set metadata
  ast->setChildDefs();
  // Print the output to cout
  fprintf(stderr,"<?xml version=\"1.0\"?>\n");
  std::ostream& err = std::cerr;
  std::ostream& out = std::cout;
  ast->print_xml(err);
  // Initialize context with cout as target
  Context ctxt(&out);
  // Print assembly
  ast->print_asm(ctxt);
  return 0;
}
