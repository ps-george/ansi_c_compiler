/*
 * selection_statement.cpp
 *
 *
 */

#include "ast/selection_statement.hpp"

/*
 * GETTERS
 */

const Expression *SelectionStatement::getCondition() const { return getConditions()[0]; };

std::vector<const Expression *>SelectionStatement::getConditions() const {
  return {cond};
}

/*
 * END OF GETTERS
 */

/*
 * PRINTERS
 */
void IfElseStatement::print_xml(std::ostream &stream) const {
  IfStatement::print_xml(stream);
  tab(stream);
  stream << getHeader() << std::endl;
  tab(stream);
  stream << "<!-- Else -->" << std::endl;
  tab_incr();
  stat2->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}
/*
 * END OF PRINTERS
 */
