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

FloatConstant::FloatConstant(const std::string &_valstr) : Constant(_valstr) {
  val = std::stof(_valstr);
};

DoubleConstant::DoubleConstant(const std::string &_valstr) : Constant(_valstr) {
  val = std::stod(_valstr);
};

/* GETTERS */

std::string Constant::getNodeType() const { return "Constant"; }
std::string StringLiteral::getNodeType() const { return "StringLiteral"; }
std::string FloatConstant::getNodeType() const { return "FloatConstant"; }
std::string DoubleConstant::getNodeType() const { return "DoubleConstant"; }
std::string IntConstant::getNodeType() const { return "IntConstant"; }
std::string EnumConstant::getNodeType() const { return "EnumConstant"; }
std::string CharConstant::getNodeType() const { return "CharConstant"; }

void Constant::print_c() const {
  Node::print_c();
  std::cout << getNodeType() << " " << getValue() << std::endl;
}

void Constant::print_asm(Context& ctxt) const {
  ctxt.ss() << "li $2, " << getValue() << " # Load constant into active register" << std::endl;
}
