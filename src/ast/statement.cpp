/*
 * statement.cpp
 *
 *
 */

#include "ast/statement.hpp"

/*
 * GETTERS
 */

std::string CompoundStatement::getNodeType() const { 
if (parser)
  return "Scope";
return "CompoundStatement"; };

std::vector<const Node *> CompoundStatement::getChildren() const {
  return {declars, stats};
}

/*
 * END OF GETTERS
 */

/*
 * PRINTERS
 */

Context CompoundStatement::print_asm(Context ctxt, int d) const {
  // Print the asm for a declaration, also update context
  //  ctxt.ss() << "## Print declars for " << getNodeType() << std::endl;
  ctxt = declars->print_asm(ctxt);
  for (auto it: stats->getChildren()){
    
    // Each of the children has no effect on context afterwards.
    // This ensures when exciting child scope, declarations are unshadowed.
    it->print_asm(ctxt,d);
  }
  return ctxt;
}

Context ExpressionStatement::print_asm(Context ctxt, int d) const {
  expr->print_asm(ctxt,d);
  return ctxt;
}


void ExpressionStatement::print_xml(std::ostream& stream) const {
if (!parser)
  Node::print_xml(stream);
}

void ConditionalStatement::print_xml(std::ostream &stream) const {
  Node::print_xml(stream);
  //tab(stream);
  //stream << getHeader() << std::endl;
  //tab_incr();
  //// cond1->print_xml();
  //stat1->print_xml(stream);
  //tab(stream,false);
  //stream << getFooter() << std::endl;
}

void CompoundStatement::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
  tab_incr();
  declars->print_xml(stream);
  stats->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}

// void Statement::print_c() const { 
//  tab();
//  std::cout << getNodeType() << ';' << std::endl;
//}

//void ConditionalStatement::print_c() const {
//  tab();
//  std::cout << "while(";
//  for (auto &it : getConditions()){
//    it->print_c();
//  }
//  std::cout << ")\n";
//  tab_incr();
//  stat1->print_c();
//  tab(false);
//}
//
//void CompoundStatement::print_c() const {
//  tab();
//  std::cout << "{\n";
//  tab_incr();
//  for (auto &it : declars->getChildren()) {
//    it->print_c();
//    std::cout << ';' << std::endl;
//  };
//  stats->print_c();
//  tab_decr();
//  tab();
//  std::cout << "}\n";
//}
