/*
 * constant.hpp
 *
 *
 */


#include "ast/variable.hpp"

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

void Variable::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
}

// void Variable::print_c() const { 
//  std::cout << getId();
//}
