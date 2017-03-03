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
