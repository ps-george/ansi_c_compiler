/*
 * constant.hpp
 *
 *
 */


#include "ast/variable.hpp"


/* GETTERS */

std::string Variable::getNodeType() const { return "Variable"; }
std::string Parameter::getNodeType() const { return "Parameter"; }

std::string Variable::getType() const { return type->getTypename(); }

std::string Variable::getId() const { return id; };

std::string Variable::getHeader() const { 
  return "<" + getNodeType() 
             + " id=\"" + getId() 
             + "\" type=\"" + getType()
             + "\" " + Node::getDeets() + "/>";
}

/* PRNT ASM */
Context Variable::print_asm(Context ctxt) const {
  ctxt.ss() << "\tlw $2," << ctxt.getVariable(id) << "($fp)" << " # load variable from fp" << std::endl; 
  return ctxt;
}


/* PRINT XML */

void Variable::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
}
