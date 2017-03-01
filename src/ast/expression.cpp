/*
 * expression.cpp
 *
 *
 */

#include "ast/expression.hpp"

//std::string Expression::getNodeType() const { return "Expression"; };
std::string EmptyExpression::getNodeType() const { return "EmptyExpression"; };
std::string TrinaryExpression::getNodeType() const { return "TrinaryExpression"; };

std::vector<const Node *> TrinaryExpression::getChildren() const{
  return {left,middle,right};
}

// void TrinaryExpression::print_c() const { 
//  left->print_c();
//  std::cout << " ? ";
//  middle->print_c();
//  std::cout << " : ";
//  right->print_c();
//}
