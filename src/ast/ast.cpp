/*
 * ast.cpp
 *
 *
 */

#include "ast.hpp"

const Node *List::add(const Node *child) const {
  children.push_back(child);
  return this;
};
/*
const ExpressionList *ExpressionList::add(const Expression *child) const {
  children.push_back(child);
  return this;
};
*/

List::~List() {
  for (auto &it : children)
    delete it;
  children.clear();
}


/*
 * Compile functions
 */

void AssignmentExpression::compile() const {
  if (op == "=") {

  } else if (op == "*=") {

  } else if (op == "/=") {

  } else if (op == "%=") {

  } else if (op == "+=") {

  } else if (op == "-=") {

  } else if (op == "&=") {

  } else if (op == "|=") {

  } else if (op == "^=") {

  } else if (op == "<<=") {

  } else if (op == ">>=") {

  } else {
    throw std::runtime_error("Unknown construct '" + op + "'");
  }
}

/*
 * END OF COMPILE functions
 */
/*
* PRINT CPP functions
*/
void Node::print_cpp() const {
  tab();
  std::cout << getType() << std::endl;
  tab_incr();
  // print_children();
  tab(0);
  std::cout << getFooter() << std::endl;
};
/*
 * END OFPRINT CPP functions
 */
/*
 * PRINT XML functions
 */
void Node::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  // print_children();
  tab(0);
  std::cout << getFooter() << std::endl;
};

void TabbedList::print_xml() const {
  if (getChildren().size() != 0) {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
    // Print out all children on the same level -> Using list to store lots
    // lists of things
    print_children();
    tab(false);
    std::cout << getFooter() << std::endl;
  } else {
    tab_decr();
  }
}

void List::print_children() const {
  for (auto &it : getChildren()) {
    it->print_xml();
  }
};

void ConditionalStatement::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  // cond1->print_xml();
  stat1->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
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

void CompoundStatement::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  declars->print_xml();
  stats->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}

void Function::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  params->print_xml();
  stat->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}

/*
 * END OF PRINT XML functions
 */
