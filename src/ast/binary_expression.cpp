/*
 * binary_expression.cpp
 */

#include <assert.h>
#include "codegen_helpers.hpp"
#include "ast/binary_expression.hpp"

/* CONSTRUCTOR */
BinaryExpression::BinaryExpression(const Expression *l, const Expression *r,
                                   std::string *_op)
    : left(l), right(r), op(*_op) {}

/* GETTERS */

std::string BinaryExpression::getNodeType() const {
  return "BinaryExpression"; 
}
std::string AssignmentExpression::getNodeType() const { 
  return "AssignmentExpression"; 
}
std::string BinaryExpression::getDeets() const {
   return " op=\"" + getOp() + "\" " + Node::getDeets();
}

std::string BinaryExpression::getOp() const { return op; };
std::vector<const Node *> BinaryExpression::getChildren() const {
  return {left, right};
}

std::vector<std::string> BinaryExpression::getTypeVec() const {
  std::vector<std::string> v1,v2;
  
  v1 = left->getTypeVec();
  v2 = right->getTypeVec();
  for (int i = 0; i < 4; i++){
    assert(v1[i]==v2[i]);
  }
  return v1;
}


/* PRINT ASM */
Context BinaryExpression::print_asm(Context ctxt, int d) const {
  // ctxt.ss() << "# Binary expression, operator: '" << getOp() <<"' " << std::endl;
  
  //ctxt.ss() << "## Binary expression, dest =" << d << std::endl;
  
  std::string endlabel = "bend" + getUnq();
  if (!(op=="&&" || op=="||")){
    // Compile the left into a specific register, without changing anything else
    getLeft()->print_asm(ctxt,3);
    // Need to save and restore previous value of 3
    // Store 3 on the stack
    // reserve space
    ctxt.push(3);
    getRight()->print_asm(ctxt,2);
    ctxt.pop(3);
  }
  else if (op=="||"){
    // If either one is not equal to 0, set to 1
    // If first argument is > 0, set to one, then 
    // LHS
    getLeft()->print_asm(ctxt,3);
    ctxt.ss() << "\tsltu\t$" << d << ",$0,$3" << " # check if left is greater than zero" << std::endl;
    ctxt.ss() << "\tbeq\t$"  << d << ",1," << endlabel << " # if it is > zero, short circuit" << std::endl;
    ctxt.ss() << "\tnop" << std::endl;
    // RHS
    ctxt.push(3);
    getRight()->print_asm(ctxt,2);
    ctxt.pop(3);
    ctxt.ss() << "\tsltu\t$" << d << ",$0,$2" << " # check if right is greater than zero" << std::endl;
    ctxt.ss() << "\tbeq\t$"  << d << ",1," << endlabel << " # if it is != zero, short circuit" << std::endl;
    ctxt.ss() << "\tnop" << std::endl;
    ctxt.ss() << endlabel << ":" << std::endl;
    //ctxt.ss() << "\tor\t$" << d << ",$2,$3" << " # " << std::endl;
  }
  else if (op=="&&"){
    // If either one is equal to 0, set to 0
    // \todo shortcircuiting!
    // LHS
    getLeft()->print_asm(ctxt,3);
    ctxt.ss() << "\txor\t$" << d << ",$3,$0" << " # xor left with 0" << std::endl;
    ctxt.ss() << "\tsltu\t $" << d << ",$0,$3" << " # check if it is greater than zero" << std::endl;
    ctxt.ss() << "\tbeq\t$"  << d << ",$0," << endlabel << " # if it is == zero, short circuit" << std::endl;
    ctxt.ss() << "\tnop" << std::endl;
    // RHS
    ctxt.pop(3);
    getRight()->print_asm(ctxt,2);
    ctxt.pop(3);
    ctxt.ss() << "\txor\t$" << d << ",$2,$0" << " # xor left with 0" << std::endl;
    ctxt.ss() << "\tsltu\t $" << d << ",$0,$2" << " # check if it is less than 1" << std::endl;
    ctxt.ss() << "\tbeq\t$"  << d << ",$0," << endlabel << " # if it is == zero, short circuit" << std::endl;
    ctxt.ss() << "\tnop" << std::endl;
    ctxt.ss() << endlabel << ":" << std::endl;
  }
  // Arithmetic Operators
  if (op == "+"){
    
    //if (getType() == Int){
      ctxt.ss() << "\tadd\t$" << d << ",$3,$2" << " # add $3 and $2" << std::endl;
    //}
    //else if (getType() == ){
    //}
  } else if (op=="-"){
    ctxt.ss() << "\tsub\t$" << d << ",$3,$2" << " # sub $3-$2" << std::endl;
  } else if (op=="*"){
    ctxt.ss() << "\tmul\t$" << d << ",$3,$2" << " # mul $3*$2" << std::endl;
  } else if (op=="/"){
    ctxt.ss() << "\tdiv\t$" << d << ",$3,$2" << " # div $3/$2" << std::endl;
  } else if (op=="%"){
    ctxt.ss() << "\tdiv\t$" << d << ",$3,$2" << " # div $3/$2" << std::endl;
    ctxt.ss() << "\tmfhi\t$" << d << " # get modulo component $3%$2" << std::endl;
  }
  // Binary Operators
  else if (op=="^"){
    ctxt.ss() << "\txor\t$" << d << ",$3,$2" << " # xor $3*$2" << std::endl;
  }
  else if (op=="&"){
    ctxt.ss() << "\tand\t$" << d << ",$3,$2" << " # and $3*$2" << std::endl;
  }
  else if (op=="|"){
    ctxt.ss() << "\tor\t$" << d << ",$3,$2" << " # or $3*$2" << std::endl;
  }
  
  // Relational expressions
  // \todo would need to check for signed/unsigned-ness in type of operands
  // Assume all unsigned for now
  else if (op=="<"){
    ctxt.ss() << "\tsltu\t $" << d << ",$3,$2" << " # check if it is less than 1" << std::endl;
  }
  else if (op==">"){
    ctxt.ss() << "\tsgtu\t $" << d << ",$3,$2" << " # check if it is less than 1" << std::endl;
  }
  else if (op=="<="){
    ctxt.ss() << "\tsleu\t $" << d << ",$3,$2" << " # check if it is less than 1" << std::endl;
  }
  else if (op==">="){
    ctxt.ss() << "\tsgeu\t $" << d << ",$3,$2" << " # check if it is less than 1" << std::endl;
  }
  // Equality expressions
  else if (op=="=="){
    ctxt.ss() << "\txor\t $3,$3,$2" << " # xor left with right" << std::endl;
    ctxt.ss() << "\tsltu\t $" << d << ",$3,1" << " # check if it is less than 1" << std::endl;
    //ctxt.ss() << "\tandi $2,$2,0x00ff" << " # not sure this is necessary" << std::endl; 
  } else if (op=="!="){
    ctxt.ss() << "\txor\t $3,$3,$2" << " # xor left with right" << std::endl;
    ctxt.ss() << "\tsltu\t $" << d << ",$0,$3" << " # check if it is less than 1" << std::endl;
    //ctxt.ss() << "\tandi $2,$2,0x00ff" << " # not sure this is necessary" << std::endl; 
  } else {
    ctxt.ss() << "### BINARY OPERATOR\'" << op << "\' NOT IMPLEMENTED YET" << std::endl;
  }
  
  //fprintf(ctxt.ss(), "%s:", endlabel);
  
  return ctxt;
}

Context AssignmentExpression::print_asm(Context ctxt, int d) const {
  if (op == "=") {
    getRight()->print_asm(ctxt);
    ctxt.storeVariable(getLeft()->getId(), 2);
    return ctxt;
  } else {
    // Store left in $3
    getLeft()->print_asm(ctxt,3);
    ctxt.push(3);
    // Store right in $2
    getRight()->print_asm(ctxt,2);
    ctxt.pop(3);
  }
  
  if (op == "*=") {
    // Left = Left * Right
    ctxt.ss() << "\tmul\t$2,$3,$2" << " # mul $3*$2" << std::endl;
    
  } else if (op == "/=") {
    // Left = Left / Right
    ctxt.ss() << "\tdiv\t$2,$3,$2" << " # div $3/$2" << std::endl;

  } else if (op == "%=") {
    // Left = Left % Right
    ctxt.ss() << "\tmod\t$2,$3,$2" << " # mod $3%$2" << std::endl;
  } else if (op == "+=") {
    // Left = Left + Right
    // If variable is unsigned do addu
    ctxt.ss() << "\tadd\t$2,$3,$2" << " # add $3+$2" << std::endl;
  } else if (op == "-=") {
    // Left = Left - Right
    // // If variable is unsigned do subu
    ctxt.ss() << "\tsub\t$2,$3,$2" << " # sub $3-$2" << std::endl;
  } else if (op == "&=") {
    // Left = Left & Right
    ctxt.ss() << "\tand\t$2,$3,$2" << " # and $3&$2" << std::endl;
  } else if (op == "|=") {
    // Left = Left | Right
    ctxt.ss() << "\tor\t$2,$3,$2" << " # or $3|$2" << std::endl;
  } else if (op == "^=") {
    // Left = Left ^ Right
    ctxt.ss() << "\txor\t$2,$3,$2" << " # xor $3^$2" << std::endl;
  } else if (op == "<<=") {
    // Left = Left ^ Right
    ctxt.ss() << "\tlsl\t$2,$3,$2" << " # << $3<<$2" << std::endl;
  } else if (op == ">>=") {
    // Left = Left ^ Right
    // If variable is unsigned, do lsr
    ctxt.ss() << "\tasr\t$2,$3,$2" << " # >> $3>>$2" << std::endl;
  } else {
    throw std::runtime_error("Unknown construct '" + op + "'");
  }
  ctxt.storeVariable(getLeft()->getId(), 2);
  return ctxt;
}

void BinaryExpression::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
  tab_incr();
  tab(stream,true);
  stream << "<!-- Left -->" << std::endl;
  left->print_xml(stream);
  tab(stream,false);
  stream << "<!-- Left /-->" << std::endl;
  tab(stream,true);
  stream << "<!-- Right -->" << std::endl;
  right->print_xml(stream);
  tab(stream,false);
  stream << "<!-- Right /-->" << std::endl;
  
  tab_decr();
  tab(stream);
  stream << getFooter() << std::endl;
};



/* PRINT C */
// void BinaryExpression::print_c() const { 
//  left->print_c();
//  std::cout << " " << getOp() << " ";
//  right->print_c();
//}
