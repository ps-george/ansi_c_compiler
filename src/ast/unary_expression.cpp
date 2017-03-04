/*
 * unary_expression.cpp
 *
 *
 */

#include "ast/unary_expression.hpp"

/* GETTERS */
std::string UnaryExpression::getNodeType() const { return "UnaryExpression";}
std::string PostfixExpression::getNodeType() const { return "PostfixExpression";}
std::string PrefixExpression::getNodeType() const { return "PrefixExpression";}
std::string FunctionCall::getNodeType() const { return "FunctionCall";}

/* END OF GETTERS */





/* PRINT C */
// void UnaryExpression::print_c() const { 
//  child->print_c(); 
//}
