/*
 * binary_expression.cpp
 *
 *
 */

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
void BinaryExpression::print_asm(Context& ctxt) const {
  // ctxt.ss() << "# Binary expression, operator: '" << getOp() <<"' " << std::endl;
  
  // Compile the right into a specific register i.e. $3. 
  getRight()->print_asm(ctxt);
  // Right now everything goes to $3, so need to move to $3 first
  ctxt.ss() << "\tmove\t$3,$2" << " # move results of right hand side into $3 for addition" << std::endl;
  // Compile the left into a specific register i.e. $2
  getLeft()->print_asm(ctxt);
  
  // Add the two results
  ctxt.ss() << "\tadd\t$2,$2,$3" << " # add $2 and $3" << std::endl;
}

void AssignmentExpression::print_asm(Context& ctxt) const {
  //ctxt.ss() << "# assignment expression with op: '"<<op<<"'"<<std::endl;
  if (op == "=") {
    // Load the offset of the thing on the left.
    int offset = ctxt.getVariable(getLeft()->getId());
    
    // Compile the right hand side into the register that we'll be saving
    getRight()->print_asm(ctxt);
    
    // Store it back in the same place
    ctxt.ss() << "\tsw\t$2," << offset << "($fp)" << " # store back in the same place" << std::endl;
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
}

















/* PRINT C */
// void BinaryExpression::print_c() const { 
//  left->print_c();
//  std::cout << " " << getOp() << " ";
//  right->print_c();
//}
