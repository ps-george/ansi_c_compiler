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

Context TrinaryExpression::print_asm(Context ctxt, int d) const {
  std::string UNQ = getUnq();
  ctxt = left->print_asm(ctxt,d);
  std::string tritrue = "tritrue" + UNQ;
  std::string trifalse = "trifalse" + UNQ;
  std::string triend = "triend" + UNQ;
  // If the first operand is equal to zero, do the third one
  ctxt.ss() << "\tbeq\t$0,$" << d << "," << trifalse << std::endl;
  ctxt = middle->print_asm(ctxt,d);
  ctxt.ss() << "\tj\t" << triend << "\n\tnop" << std::endl;
  ctxt.ss() << trifalse  << ":" << std::endl;
  ctxt = right->print_asm(ctxt,d);
  
  ctxt.ss() << triend  << ":" << std::endl;
  return ctxt;
}

void Expression::print_xml(std::ostream& stream) const {
  if (!parser) {
    Node::print_xml(stream);
  }
}
