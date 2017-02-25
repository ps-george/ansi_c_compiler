/*
 * constant.cpp
 *
 *
 */

#include "ast/constant.hpp"

void Constant::print_c() const {
  Node::print_c();
  std::cout << getNodeType() << " " << getValue() << std::endl;
}
