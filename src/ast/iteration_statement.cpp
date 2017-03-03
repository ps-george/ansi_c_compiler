/*
 * iteration_statement.cpp
 *
 *
 */

#include "ast/iteration_statement.hpp"

std::string IterationStatement::getNodeType() const { return "IterationStatement"; }
std::string ForStatement::getNodeType() const { return "ForStatement"; }
std::string WhileStatement::getNodeType() const { return "WhileStatement"; }
std::string DoWhileStatement::getNodeType() const { return "DoWhileStatement"; }

/*
 * GETTERS
 */

std::vector<const Node*> WhileStatement::getChildren() const {
  return {cond,stat1};
}

std::vector<const Node*> ForStatement::getChildren() const {
  return {cond1,stat1};
}

std::vector<const Node*> EEForStatement::getChildren() const {
  return {cond1,cond2,stat1};
}

std::vector<const Node*> EEEForStatement::getChildren() const {
  return {cond1,cond2,cond3,stat1};
}

std::vector<const Node*> DEForStatement::getChildren() const {
  return {dec,cond1,stat1};
}

std::vector<const Node*> DEEForStatement::getChildren() const {
  return {dec,cond1,cond2,stat1};
}

/*
 * END OF GETTERS
 */

/*
 * PRINTERS
 */
/*
void DEForStatement::print_xml(std::ostream& stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
  tab_incr();
  dec->print_xml(stream);
  stat1->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}
*/

/*
 * END OF PRINTERS
 */

// void IterationStatement::print_c() const { 
  // while ()
//  std::cout << getNodeType() << " (";
//  for (auto &it : getConditions()) {
//    it->print_c();
//  }
//  std::cout << ")\n";
//  tab();
//  getBody()->print_c();
//};
