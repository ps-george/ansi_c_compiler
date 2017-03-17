/*
 * constant.cpp
 *
 *
 */

#include "ast/constant.hpp"

/* CONSTRUCTORS */

Constant::Constant(const std::string &_valstr) : valstr(_valstr){};

IntConstant::IntConstant(const std::string &_valstr) : Constant(_valstr) {
  val = std::stoi(_valstr);
};

CharConstant::CharConstant(const std::string &_valstr) : Constant(_valstr) {
  val = _valstr[0];
}

FloatConstant::FloatConstant(const std::string &_valstr) : Constant(_valstr) {
  val = std::stof(_valstr);
};

DoubleConstant::DoubleConstant(const std::string &_valstr) : Constant(_valstr) {
  val = std::stod(_valstr);
};

StringLiteral::StringLiteral(const std::string &_valstr) : Constant(_valstr){
  Node::addString(_valstr); 
};

/* GETTERS */

std::string Constant::getNodeType() const { return "Constant"; }
std::string StringLiteral::getNodeType() const { return "StringLiteral"; }
std::string FloatConstant::getNodeType() const { return "FloatConstant"; }
std::string DoubleConstant::getNodeType() const { return "DoubleConstant"; }
std::string IntConstant::getNodeType() const { return "IntConstant"; }
std::string EnumConstant::getNodeType() const { return "EnumConstant"; }
std::string CharConstant::getNodeType() const { return "CharConstant"; }

/* PRINT ASM */
Context IntConstant::print_asm(Context ctxt, int d) const {
  ctxt.ss() << "\tli $" << d <<"," << getValue() << " # Load constant into active register" << std::endl;
  return ctxt;
}

Context FloatConstant::print_asm(Context ctxt, int d) const {
  ctxt.ss() << "\tli $" << d <<"," << getValue() << " # Load constant into active register" << std::endl;
  return ctxt;
}

Context StringLiteral::print_asm(Context ctxt, int d) const {
  ctxt.ss() << "\tli $" << d <<"," << getValue() << " # Load constant into active register" << std::endl;
  // lui	$2,%hi($LC0)
	// addiu	$2,$2,%lo($LC0)
  return ctxt;
}

/* PRINT XML */
void Constant::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
}


// void Constant::print_c() const { 
//  Node::print_c();
//  std::cout << getNodeType() << " " << getValue() << std::endl;
//}
