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

/*
void JumpStatement::print_asm(Context& ctxt, int vars) const {
  // Move the frame pointer to stack pointer
  ctxt.ss() << "\tmove $sp,$fp" << std::endl
  // Load the previous frame pointer (unwind)
  << "\tlw $fp," << vars+4 <<"($sp)" << std::endl
  // Unallocate the frame we were in
  << "\taddiu $sp,$sp," << vars+8 << std::endl
  // Return
  << "\tj $31\n\tnop" << std::endl;
}*/
/*
void ReturnStatement::print_asm(Context& ctxt, int vars) const{
  expr->print_asm(ctxt);
  JumpStatement::print_asm(ctxt,vars);
}
*/

/*
 * PRINT XML
 */

void JumpStatement::print_xml(std::ostream& stream) const {
  if (!parser){
    Node::print_xml(stream);
  }
}
