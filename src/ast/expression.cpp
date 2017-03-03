/*
 * expression.cpp
 *
 *
 */

#include "ast/expression.hpp"

/*
 * GETTERS
 */
//std::string Expression::getNodeType() const { return "Expression"; };
std::string EmptyExpression::getNodeType() const { return "EmptyExpression"; };
std::string TrinaryExpression::getNodeType() const { return "TrinaryExpression"; };

std::vector<const Node *> TrinaryExpression::getChildren() const{
  return {left,middle,right};
}

/*
 * END OF GETTERS
 */
