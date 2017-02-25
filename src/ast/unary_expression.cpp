/*
 * unary_expression.cpp
 *
 *
 */

#include "ast/unary_expression.hpp"


void UnaryExpression::print_c() const {
  child->print_c(); 
}
