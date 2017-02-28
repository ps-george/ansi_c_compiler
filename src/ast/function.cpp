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


std::vector<const Node *> Function::getChildren() const{
  std::cerr << "Finding children of " << declarator->getId() << ":" << std::endl;
  return {declarator, stat};
}

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
  setChildDefs();
  std::vector<std::string> vars = getChildDefs();
  int vars_size = vars.size()*4;
  std::cerr << vars_size << std::endl;
  // Indicated that we're printing out a function
  ctxt.ss() << "# Function " << declarator->getId() << std::endl
  // Label for the function
  << declarator->getId() << ":" << std::endl
  // Need to know the number of variables in the function..!
  << "\t.frame $fp,f" << "# vars="<< vars_size <<" , regs= 1/0, args= 0, gp= 0" << std::endl
  << "\t.mask = 0x40000000,-4" << std::endl
  << "\taddiu $sp, $sp,-" << vars_size+8 << " #(insert vars + 8)" << std::endl
  << "\tsw $fp,"<< vars_size+4 << "($sp)" << std::endl
  << "\tmove $fp, $sp" << std::endl;
}
