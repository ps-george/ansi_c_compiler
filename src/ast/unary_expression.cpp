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

void FunctionCall::setParamUses() const {
  for (auto it: args->getChildren()){
    childParams.push_back(it->getId());
  }
}



Context FunctionCall::print_asm(Context ctxt, int d) const {
  // If there is an expression in the functioncall, evaluate and move to $4
  // Want $3 to be preserved
  ctxt.ss() << "\tmove $16,$3" << " # want to preserve $3 across calls" << std::endl;
  // Before a function call, reserve space on the stack for something or other (gp?)
  int i = 0;
  int k = 16;
  for (auto it: args->getChildren()){
    if (i<4){
      it->print_asm(ctxt);
      ctxt.ss() << "\tmove $" << std::to_string((i++)+4) << ",$2" << std::endl;
    }
    else {
      it->print_asm(ctxt);
      ctxt.ss() << "\tsw\t$2," << (i++)*4 << "($sp)" << std::endl;
      k+=4;
    }
  }
  
  
  ctxt.ss() << "\t.option\tpic0" << std::endl
  
  << "\tjal\t" << getId() << std::endl
  << "\tnop" << std::endl << std::endl << "\t.option\tpic2" << std::endl;
  ctxt.ss() << "\tmove $3,$16" << " # want to preserve $3 across calls" << std::endl;
  ctxt.ss() << "\tmove $" << d << ",$2" <<std::endl;
  // After a function call, restore space on the stack
  return ctxt;
}

Context PrefixExpression::print_asm(Context ctxt, int d) const {
  if (op=="++"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tadd\t$" << d << ",$" << d << ",1" << " # preincrement" << std::endl;
    // Store it back again
    
    ctxt.storeVariable(child->getId(),d);
  }
  else if (op=="--"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tsub\t$" << d <<",$" << d << ",1" << " # predecrement" << std::endl;
    // Store it back again
    ctxt.storeVariable(child->getId(),d);
  }
  else if (op=="&"){
    ctxt.ss() << "\taddiu\t$" << d << ",$fp," << ctxt.getVarOffset(child->getId()) << std::endl;
  }
  else if (op=="*"){
    ctxt.ss() << "\tlw\t$" << d << "," << ctxt.getVarOffset(child->getId()) << "($fp)" << std::endl;
    ctxt.ss() << "\tlw\t$" << d << ",0($" << d << ")" << std::endl;
  }
  return ctxt;
}

Context SquareOperator::print_asm(Context ctxt, int d) const {
  // Evaluate the expression into a REGISTER
  //ctxt = arg->print_asm(ctxt,8);
  int index = 0;
  if (arg->getNodeType()=="IntConstant"){
    index = std::stoi(arg->getId(),0,0);
  }
  else{
    ctxt = arg->print_asm(ctxt,8);
  }
  // Load the value of offset from $fp
  //int offset = ctxt.getVarOffset(child->getId());
  // Load ptr value from a
  ctxt.ss() << "\tlw\t$" << d << "," << ctxt.getVarOffset(child->getId()) << "($fp)" << std::endl;
  ctxt.ss() << "\tsll\t$8,$8,2" << std::endl;
  ctxt.ss() << "\taddu\t$" << d << ",$8,$" << d << std::endl;
  //ctxt.ss() << "\taddu\t$" << d << ",$fp,$" << d <<std::endl;
  ctxt.ss() << "\tlw\t$" << d << ",0" << "($"<<d<<")" << std::endl;  
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
    ctxt.storeVariable(child->getId(),4);
  }
  else if (op=="--"){
    child->print_asm(ctxt,d); // Loads child into $2
    ctxt.ss() << "\tsub\t$4, $" << d << ",1" << " # postdecrement" << std::endl;
    // Store it back again
    ctxt.storeVariable(child->getId(),4);
  }
  
  return ctxt;
}




/* PRINT C */
// void UnaryExpression::print_c() const { 
//  child->print_c(); 
//}
