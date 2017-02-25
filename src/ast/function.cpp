/*
 * function.cpp
 *
 *
 */

#include "ast/function.hpp"

void Function::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  declarator->print_xml();
  stat->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}
