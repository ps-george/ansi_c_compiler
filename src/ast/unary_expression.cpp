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
std::string CastExpression::getNodeType() const { return "CastExpression";}
std::string FunctionCall::getNodeType() const { return "FunctionCall";}

/* END OF GETTERS */

Context FunctionCall::print_asm(Context ctxt, int d) const {
  // If there is an expression in the functioncall, evaluate and move to $4
  // Want $3 to be preserved
  ctxt.ss() << "\tmove $16,$3" << " # want to preserve $3 across calls" << std::endl;
  int i = 4;
  for (auto it: args->getChildren()){
    if (i<8){
      it->print_asm(ctxt);
      // For now only consider functions of one variable
      ctxt.ss() << "\tmove $" << std::to_string(i++) << ",$2" << std::endl;
    }
    else {
      it->print_asm(ctxt);
      ctxt.ss() << "\tsw\t$2," << ((i++)-4)*4 << "($sp)" << std::endl;
    }
  }
  
  
  ctxt.ss() << "\t.option\tpic0" << std::endl
  
  << "\tjal\t" << getId() << std::endl
  << "\tnop" << std::endl << std::endl << "\t.option\tpic2" << std::endl;
  ctxt.ss() << "\tmove $3,$16" << " # want to preserve $3 across calls" << std::endl;
  ctxt.ss() << "\tmove $" << d << ",$2" <<std::endl;
  return ctxt;
}

Context PrefixExpression::print_asm(Context ctxt, int d) const {
  if (op=="++"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tadd\t$" << d << ",$" << d << ",1" << " # preincrement" << std::endl;
    // Store it back again
    
    store(ctxt,child->getId(),d);
  }
  else if (op=="--"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tsub\t$" << d <<",$" << d << ",1" << " # predecrement" << std::endl;
    // Store it back again
    store(ctxt,child->getId(),d);
  }
  return ctxt;
}

Context CastExpression::print_asm(Context ctxt, int d) const {
  
  return ctxt;
}

Context PostfixExpression::print_asm(Context ctxt, int d) const {
  if (op=="++"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tadd\t$4, $" << d << ",1" << " # postincrement" << std::endl;
    // Store it back again
    store(ctxt,child->getId(),4);
  }
  else if (op=="--"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tsub\t$4, $" << d << ",1" << " # postdecrement" << std::endl;
    // Store it back again
    store(ctxt,child->getId(),4);
  }
  
  return ctxt;
}




/* PRINT C */
// void UnaryExpression::print_c() const { 
//  child->print_c(); 
//}
