/*
 * expression.cpp
 *
 *
 */

#include "ast/expression.hpp"

void TrinaryExpression::print_c() const {
  left->print_c();
  std::cout << " ? ";
  middle->print_c();
  std::cout << " : ";
  right->print_c();
}
