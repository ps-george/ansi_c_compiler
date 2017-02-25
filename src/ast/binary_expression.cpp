/*
 * binary_expression.cpp
 *
 *
 */

#include "ast/binary_expression.hpp"



void AssignmentExpression::compile() const {
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
