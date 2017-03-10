/*
 * binary_expression.cpp
 *
 *
 */

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


/* PRINT ASM */
Context BinaryExpression::print_asm(Context ctxt) const {
  // ctxt.ss() << "# Binary expression, operator: '" << getOp() <<"' " << std::endl;
  
  // Compile the left into a specific register i.e. $3
  getLeft()->print_asm(ctxt);
  // Everything on left goes to $2, so need to move to $3 first 
  ctxt.ss() << "\tmove\t$3,$2" << " # move results of left hand side into $3 for operation" << std::endl;
  
  // Compile the right into a specific register i.e. $2. 
  getRight()->print_asm(ctxt);
  
  if (op == "+"){
    // Add the two results
    ctxt.ss() << "\tadd\t$2,$3,$2" << " # add $2 and $3" << std::endl;
  } else if (op=="-"){
    ctxt.ss() << "\tsub\t$2,$3,$2" << " # sub $2-$3" << std::endl;
  } else if (op=="=="){
    ctxt.ss() << "\txor\t $2,$3,$2" << " # xor left with right" << std::endl;
    ctxt.ss() << "\tsltu\t $2,$3,1" << " # check if it is less than 1" << std::endl;
    //ctxt.ss() << "\tandi $2,$2,0x00ff" << " # not sure this is necessary" << std::endl; 
  } else {
    ctxt.ss() << "### BINARY OPERATOR\'" << op << "\' NOT IMPLEMENTED YET" << std::endl;
  }
  
  return ctxt;
}

Context AssignmentExpression::print_asm(Context ctxt) const {
  //ctxt.ss() << "# assignment expression with op: '"<<op<<"'"<<std::endl;
  if (op == "=") {
    // Load the offset of the thing on the left.
    //int offset = ctxt.getVariable(getLeft()->getId());
    
    // Compile the right hand side into the register that we'll be saving
    getRight()->print_asm(ctxt);
    
    // Store it back in the same place
    store(ctxt, getLeft()->getId());
  } else if (op == "*=") {

  } else if (op == "/=") {

  } else if (op == "%=") {

  } else if (op == "+=") {

  } else if (op == "-=") {

  } else if (op == "&=") {

  } else if (op == "|=") {

  } else if (op == "^=") {

  } else if (op == "<<=") {

  } else if (op == ">>=") {

  } else {
    throw std::runtime_error("Unknown construct '" + op + "'");
  }
  return ctxt;
}

















/* PRINT C */
// void BinaryExpression::print_c() const { 
//  left->print_c();
//  std::cout << " " << getOp() << " ";
//  right->print_c();
//}
