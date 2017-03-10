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

Context FunctionCall::print_asm(Context ctxt) const {
  // If there is an expression in the functioncall, evaluate and move to $4
  int i = 4;
  for (auto it: args->getChildren()){
    it->print_asm(ctxt);
    // For now only consider functions of one variable
    ctxt.ss() << "\tmove $" << std::to_string(i++) << ",$2" << std::endl;
  }
  
  
  ctxt.ss() << "\t.option\tpic0" << std::endl
  
  << "\tjal\t" << getId() << std::endl
  << "\tnop" << std::endl << std::endl << "\t.option\tpic2" << std::endl;
  return ctxt;
}




/* PRINT C */
// void UnaryExpression::print_c() const { 
//  child->print_c(); 
//}
