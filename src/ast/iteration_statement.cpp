/*
 * iteration_statement.cpp
 *
 *
 */

#include "ast/iteration_statement.hpp"

std::string IterationStatement::getNodeType() const { return "IterationStatement"; }

void DEForStatement::print_xml(std::ostream& stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
  tab_incr();
  dec->print_xml(stream);
  stat1->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}

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
