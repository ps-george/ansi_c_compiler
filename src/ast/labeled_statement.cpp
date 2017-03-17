/*
 * labeled_statement.cpp
 *
 *
 */

#include "ast/labeled_statement.hpp"

/*
 * GETTERS
 */
std::string LabeledStatement::getNodeType() const { return "LabeledStatement"; }
std::string CaseLabel::getNodeType() const { return "CaseLabel"; }
//std::string DefaultLabel::getNodeType() const { return "DefaultLabel"; }

/*
 * END OF GETTERS
 */

/*
 * PRINT ASM
 */

// Return statement has an expression (or not expression if void function)
Context LabeledStatement::print_asm(Context ctxt, int d) const{
  ctxt.ss() << id << ": # label before labelled statement" << std::endl;
  
  ctxt = stat->print_asm(ctxt);
  return ctxt;
}

// Break and Continue statements have no expression
Context CaseLabel::print_asm(Context ctxt, int d) const {
  // Switch statement could just evaluate into $3, then these statements figure out what next
  std::string caselabel = "case" + getUnq();
  // Evaluate expression.
  ctxt.push(2);
  ctxt = expr->print_asm(ctxt,3);
  ctxt.pop(2);
  
  // If $2 != $3, skip the statement for this case label
  ctxt.ss() << "\tbne\t$2,$3," << caselabel << std::endl;
  ctxt = stat->print_asm(ctxt);

  // if expression is not equal to 
  ctxt.ss() << caselabel << ": # case label probably needs to be unique" << std::endl;
  
  
  return ctxt;
}

Context DefaultLabel::print_asm(Context ctxt, int d) const {
  
  ctxt.ss() << "default" << ": # default label, not sure if needs ot be unique" << std::endl;
  ctxt = stat->print_asm(ctxt);

  return ctxt;
}
