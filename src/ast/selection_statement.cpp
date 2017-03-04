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

void IfStatement::print_xml(std::ostream &stream) const {
  tab(stream,true);
  stream << getHeader() << " <!-- If -->" << std::endl;
  tab(stream,true);
    stream << "<Condition>" << std::endl;
        getCondition()->print_xml(stream);
    tab(stream,false);
    stream << "</Condition>" << std::endl;
    tab(stream,true);
    stream << "<Then>" << std::endl;
      stat1->print_xml(stream);
    tab(stream,false);
  stream << "</Then>" << std::endl;
  tab(stream,false);
  stream << getFooter() << std::endl;
}

void IfElseStatement::print_xml(std::ostream &stream) const {
  IfStatement::print_xml(stream);
  tab(stream);
  stream << getHeader() << " <!-- Else -->" << std::endl;
  tab_incr();
  stat2->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}
/*
 * END OF PRINTERS
 */
