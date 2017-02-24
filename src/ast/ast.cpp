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
  std::cout << "// " << getNodeType() << std::endl;
}

void List::print_children_cpp() const {
  for (auto &it : getChildren()) {
    it->print_cpp();
  }
}

void List::print_cpp() const {
  //Node::print_cpp(); 
  print_children_cpp(); 
}

void UnaryExpression::print_cpp() const {
  //Node::print_cpp(); 
  child->print_cpp(); 
}

void TrinaryExpression::print_cpp() const {
  //Node::print_cpp(); 
  left->print_cpp();
  std::cout << " ? ";
  middle->print_cpp();
  std::cout << " : ";
  right->print_cpp();
}

void BinaryExpression::print_cpp() const {
  //Node::print_cpp(); 
  left->print_cpp();
  std::cout << " " << getOp() << " ";
  right->print_cpp();
}

void Constant::print_cpp() const {
  Node::print_cpp();
  std::cout << getNodeType() << " " << getValue() << std::endl;
}

void TabbedList::print_cpp() const {
  if (getChildren().size() != 0) {
    tab_incr();
    // Print out all children on the same level -> Using list to store lots
    // lists of things
    print_children_cpp();
    tab(false);
  } else {
    tab_decr();
  }
}

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
  // print_children_xml();
  tab(0);
  std::cout << getFooter() << std::endl;
};

void Variable::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
}

void TabbedList::print_xml() const {
  if (getChildren().size() != 0) {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
    // Print out all children on the same level -> Using list to store lots
    // lists of things
    print_children_xml();
    tab(false);
    std::cout << getFooter() << std::endl;
  } else {
    tab_decr();
  }
}

void Declarator::print_xml() const{
  tab();
  std::cout << "<Variable id=\"" << getId() << "\" />" << std::endl;
}

void DeclarationList::print_xml() const{
  List::print_xml();
};

void ParameterList::print_xml() const{
  for (auto &it : getChildren()) {
    std::cout << "<Parameter id=\"" << it->getId() << "\" />" << std::endl;
  }
};

void FunctionDeclarator::print_xml() const {
  for (auto &it : p->getChildren()) {
    tab();
    std::cout << "<Parameter id=\"" << it->getId() << "\" />" << std::endl;
  }
};

void Declaration::print_xml() const{
  dlist->print_xml();
};

void List::print_children_xml() const {
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
  declarator->print_xml();
  stat->print_xml();
  tab(false);
  std::cout << getFooter() << std::endl;
}

/*
 * END OF PRINT XML functions
 */
