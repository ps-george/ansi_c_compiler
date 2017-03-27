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

std::vector<std::string> Variable::getTypeVec() const { return type->getTypeVec(); }

std::string Variable::getId() const { return id; };

std::string Variable::getHeader() const { 
  return "<" + getNodeType() 
             + " id=\"" + getId() 
             + "\" type=\"" + getType()
             + "\" " + Node::getDeets() + "/>";
}

/* PRNT ASM */
Context Variable::print_asm(Context ctxt, int d) const {
  try{
    ctxt.loadVariable(id,d);
    //ctxt.ss() << "\tlw $" << d << "," << ctxt.getVariable(id) << "($fp)" << " # load var: " << id << std::endl;
  }
  catch(std::out_of_range& e){
    std::cerr << e.what() << std::endl;
    std::cerr << getHeader() << std::endl;
    std::terminate();
  }
  return ctxt;
}


/* PRINT XML */

void Variable::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
}
