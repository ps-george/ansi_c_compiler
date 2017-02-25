/*
 * constant.hpp
 *
 *
 */


#include "ast/variable.hpp"

void Variable::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
}
