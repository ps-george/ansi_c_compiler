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

Context ReturnStatement::print_asm(Context ctxt, int d) const{
  ctxt = expr->print_asm(ctxt);
  ctxt.ss() << "\tj " << ctxt.getF() << "postamble # jump to postamble of current function" << std::endl
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
