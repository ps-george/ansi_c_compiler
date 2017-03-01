/*
 * unary_expression.cpp
 *
 *
 */

#include "ast/unary_expression.hpp"

std::string UnaryExpression::getNodeType() const { return "UnaryExpression";}

void UnaryExpression::print_c() const {
  child->print_c(); 
}
