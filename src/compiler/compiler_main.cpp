#include "tokens.hpp"
#include "c_parser.tab.h"
#include "codegen_helpers.hpp"

#include <iomanip>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <libgen.h>

// Define the instance of the variable that is declared in the header
//YYSTYPE yylval;

std::string yylfile;
extern FILE * yyin;
// Used for column number calculations
int len;
int yylcolno = 1;
int yylsourcelino = 1;

// Used for xml print indentation, static member of ast
int Node::tabcount = 0;
bool Node::parser = 0;
std::vector<std::string> Node::strings = {};
//int Node::changed = 0;

int main(int argc, char * argv[]) {
  char* filename = argv[1];
  FILE * myfile = fopen(filename, "r");
  yyin = myfile;
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
  out << "\t.file\t1 \"" << basename(filename) << "\"" << std::endl;
  ast->print_asm(ctxt);
  return 0;
}
