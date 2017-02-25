/*
 * statement.cpp
 *
 *
 */

#include "ast/statement.hpp"

std::string Statement::getNodeType() const { return "Statement"; }
std::string CompoundStatement::getNodeType() const { return "CompoundStatement"; };

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

void Statement::print_c() const {
  tab();
  std::cout << getNodeType() << ';';
  tab(false);
}

void ConditionalStatement::print_c() const {
  tab();
  std::cout << "while(";
  getCondition()->print_c();
  std::cout << ")\n";
  tab_incr();
  stat1->print_c();
  tab(false);
}

void CompoundStatement::print_c() const {
  tab();
  std::cout << "{";
  tab_incr();
  declars->print_xml();
  stats->print_xml();
  tab(false);
  std::cout << "}\n";
}
