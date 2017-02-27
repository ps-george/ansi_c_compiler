/*
 * function.cpp
 *
 *
 */

#include "ast/function.hpp"

Function::Function(const Node *_type, const Node *_dec, const Node *_s)
    : type((const Type *)_type),
      declarator((const Declarator *)_dec), // Declarator contains the params
      stat((const CompoundStatement *)_s) {};

std::string Function::getType() const { return type->getTypename(); }

std::string Function::getHeader() const {
  return "<" + getNodeType() 
             + " id=\"" + declarator->getId() 
             + "\" type=\"" + getType()
             + "\">";
}

void Function::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  declarator->print_xml();
  stat->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}

void Function::print_c() const {
  std::cout << getType() << " ";
  declarator->print_c();
  std::cout << "\n";
  stat->print_c();
}

void Function::print_asm(Context& ctxt) const{
  // Indicated that we're printing out a function
  ctxt.ss() << "\t" << "# Function" << std::endl;
  // 
}
