/*
 * selection_statement.cpp
 *
 *
 */

#include "ast/selection_statement.hpp"

const Expression *SelectionStatement::getCondition() const { return getConditions()[0]; };

std::vector<const Expression *>SelectionStatement::getConditions() const {
  return {cond};
}

void IfElseStatement::print_xml() const {
  IfStatement::print_xml();
  tab();
  std::cout << getHeader() << std::endl;
  tab();
  std::cout << "<!-- Else -->" << std::endl;
  tab_incr();
  // cond1->print_xml();
  stat2->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}
