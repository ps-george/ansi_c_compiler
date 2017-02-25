/*
 * iteration_statement.cpp
 *
 *
 */

#include "ast/iteration_statement.hpp"

const Expression *WhileStatement::getCondition() const { return cond; };

std::string IterationStatement::getNodeType() const { return "IterationStatement"; }

void IterationStatement::print_c() const {
  // while ()
  std::cout << getNodeType() << " (";
  for (auto &it : getConditions()) {
    it->print_c();
  }
  std::cout << ")\n";
  tab();
  getBody()->print_c();
};
