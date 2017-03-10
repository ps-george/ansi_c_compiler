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
Context BinaryExpression::print_asm(Context ctxt, int d) const {
  // ctxt.ss() << "# Binary expression, operator: '" << getOp() <<"' " << std::endl;
  ctxt.ss() << "## Binary expression, dest =" << d << std::endl;
  // Compile the left into a specific register, without changing anything else
  getLeft()->print_asm(ctxt,3);
  // Need to save and restore previous value of 3
  // Store 3 on the stack
  // reserve space
  ctxt.push(3);
  getRight()->print_asm(ctxt,2);
  ctxt.pop(3);
  
  if (op == "+"){
    // Add the two results
    ctxt.ss() << "\tadd\t$" << d << ",$3,$2" << " # add $3 and $2" << std::endl;
  } else if (op=="-"){
    ctxt.ss() << "\tsub\t$"<< d << ",$3,$2" << " # sub $3-$2" << std::endl;
  } else if (op=="=="){
    ctxt.ss() << "\txor\t $3,$3,$2" << " # xor left with right" << std::endl;
    ctxt.ss() << "\tsltu\t $" << d << ",$3,1" << " # check if it is less than 1" << std::endl;
    //ctxt.ss() << "\tandi $2,$2,0x00ff" << " # not sure this is necessary" << std::endl; 
  } else {
    ctxt.ss() << "### BINARY OPERATOR\'" << op << "\' NOT IMPLEMENTED YET" << std::endl;
  }
  
  return ctxt;
}

Context AssignmentExpression::print_asm(Context ctxt, int d) const {
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
