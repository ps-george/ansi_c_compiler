/*
 * jump_statement.cpp
 *
 *
 */

#include "ast/jump_statement.hpp"

/*
 * GETTERS
 */
std::string JumpStatement::getNodeType() const { return "JumpStatement"; }
std::string GotoStatement::getNodeType() const { return "GotoStatement"; }
std::string ContinueStatement::getNodeType() const { return "ContinueStatement"; }
std::string BreakStatement::getNodeType() const { return "BreakStatement"; }
std::string ReturnStatement::getNodeType() const { return "ReturnStatement"; }

std::vector<const Node *> ReturnStatement::getChildren() const { return {expr}; }

/*
 * END OF GETTERS
 */

/*
 * PRINT ASM
 */


//Context JumpStatement::print_asm(Context ctxt, int d) const {
//}

// Return statement has an expression (or not expression if void function)
Context ReturnStatement::print_asm(Context ctxt, int d) const{
  ctxt = expr->print_asm(ctxt);
  ctxt.ss() << "\tj " << ctxt.getF() << "postamble # jump to postamble of current function" << std::endl
  << "\tnop\n";
  return ctxt;
}

// Break and Continue statements have no expression
Context BreakStatement::print_asm(Context ctxt, int d) const{
  
  ctxt.ss() << "\tj " << ctxt.getBreak() << " # jump to end of current loop" << std::endl
  << "\tnop\n";
  return ctxt;
}

Context ContinueStatement::print_asm(Context ctxt, int d) const{
  
  ctxt.ss() << "\tj " << ctxt.getContinue() << "# jump to beginning of current loop" << std::endl
  << "\tnop\n";
  return ctxt;
}

Context GotoStatement::print_asm(Context ctxt, int d) const{
  
  ctxt.ss() << "\tj " << label << "# jump to named label" << std::endl
  << "\tnop\n";
  return ctxt;
}


/*
 * PRINT XML
 */

void JumpStatement::print_xml(std::ostream& stream) const {
  if (!parser){
    Node::print_xml(stream);
  }
}
