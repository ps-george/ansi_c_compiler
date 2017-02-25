/*
 * list.cpp
 *
 *
 */

#include "ast/list.hpp"


std::string List::getNodeType() const { return "List"; };
std::string TabbedList::getNodeType() const { return "Scope"; }
std::string Program::getNodeType() const { return "Program"; }
std::string DeclarationList::getNodeType() const { return "DeclarationList"; }
std::string ParameterList::getNodeType() const { return "ParameterList"; }

/* COMMON FUNCTIONS */
std::vector<const Node *> List::getChildren() const { return children; };

List::~List() {
  for (auto &it : children)
    delete it;
  children.clear();
}

void List::print_children_xml() const {
  for (auto &it : getChildren()) {
    it->print_xml();
  }
};

void List::print_children_cpp() const {
  for (auto &it : getChildren()) {
    it->print_c();
  }
}

const Node *List::add(const Node *child) const {
  children.push_back(child);
  return this;
};

/* END OF COMMON FUNCTIONS */

/* PRINT XML */

void List::print_xml() const {
  print_children_xml();
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

void DeclarationList::print_xml() const{
  List::print_xml();
};

void ParameterList::print_xml() const{
  for (auto &it : getChildren()) {
    std::cout << "<Parameter id=\"" << it->getId() << "\" />" << std::endl;
  }
};

/* PRINT C */

void List::print_c() const {
  print_children_cpp(); 
}

void TabbedList::print_c() const {
  if (getChildren().size() != 0) {
    //tab_incr();
    // Print out all children on the same level -> Using list to store lots
    // lists of things
    print_children_cpp();
  }
}
