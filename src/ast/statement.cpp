/*
 * statement.cpp
 *
 *
 */

#include "ast/statement.hpp"

void ConditionalStatement::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  // cond1->print_xml();
  stat1->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}

void CompoundStatement::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  declars->print_xml();
  stats->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}
