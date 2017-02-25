/*
 * expression.cpp
 *
 *
 */

#include "ast/expression.hpp"

std::string Expression::getNodeType() const { return "Statement"; };
std::string EmptyExpression::getNodeType() const { return "EmptyExpression"; };
std::string TrinaryExpression::getNodeType() const { return "TrinaryExpression"; };

void TrinaryExpression::print_c() const {
  left->print_c();
  std::cout << " ? ";
  middle->print_c();
  std::cout << " : ";
  right->print_c();
}
