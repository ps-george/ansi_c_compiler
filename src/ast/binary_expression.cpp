/*
 * binary_expression.cpp
 *
 *
 */

#include "ast/binary_expression.hpp"

std::string BinaryExpression::getNodeType() const {
  return "BinaryExpression"; 
}
std::string AssignmentExpression::getNodeType() const { 
  return "AssignmentExpression"; 
}
std::string BinaryExpression::getDeets() const {
   return " op=\"" + getOp() + "\" " + Node::getDeets();
}

BinaryExpression::BinaryExpression(const Expression *l, const Expression *r,
                                   std::string *_op)
    : left(l), right(r), op(*_op) {}

std::string BinaryExpression::getOp() const { return op; };
std::vector<const Node *> BinaryExpression::getChildren() const {
  return {left, right};
}

void BinaryExpression::print_asm(Context& ctxt) const {
  ctxt.ss() << "# Binary expression, operator: '" << getOp() <<"' " << std::endl;
}

void AssignmentExpression::print_asm(Context& ctxt) const {
  ctxt.ss() << "# assignment expression with op: '"<<op<<"'"<<std::endl;
  if (op == "=") {
    // Load the thing on the left.
    int offset = ctxt.getVariable(getLeft()->getId());
    
    ctxt.ss() << "\tlw	$2," << offset << "($fp)"
     << " # load left hand side into a register." << std::endl;
    // The above is kind of pointless for an assignment; we will overwrite anyway 
     
    // Compiile the right hand side into the register that we'll be saving
    getRight()->print_asm(ctxt);
    
    // Store it back in the same place
    ctxt.ss() << "\tsw  $2," << offset << "($fp)" << " # store back in the same place" << std::endl;
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

// void BinaryExpression::print_c() const { 
//  left->print_c();
//  std::cout << " " << getOp() << " ";
//  right->print_c();
//}
