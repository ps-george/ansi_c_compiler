/*
 * binary_expression.cpp
 *
 *
 */

#include "ast/binary_expression.hpp"

BinaryExpression::BinaryExpression(const Expression *l, const Expression *r,
                                   std::string *_op)
    : left(l), right(r), op(*_op) {}

std::string BinaryExpression::getOp() const { return op; };
std::vector<const Node *> BinaryExpression::getChildren() const {
  return {left, right};
}

void BinaryExpression::print_asm(Context& ctxt) const {
  
}

void AssignmentExpression::print_asm(Context& ctxt) const {
  if (op == "=") {
    
  } else if (op == "*=") {

  } else if (op == "/=") {

  } else if (op == "%=") {

  } else if (op == "+=") {

  } else if (op == "-=") {

  } else if (op == "&=") {

  } else if (op == "|=") {

  } else if (op == "^=") {

  } else if (op == "<<=") {

  } else if (op == ">>=") {

  } else {
    throw std::runtime_error("Unknown construct '" + op + "'");
  }
}

void BinaryExpression::print_c() const {
  left->print_c();
  std::cout << " " << getOp() << " ";
  right->print_c();
}
