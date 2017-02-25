/*
 * node.cpp
 *
 *
 */

#include "ast/node.hpp"

//! Return the xml header for the node
std::string Node::getHeader() const { return "<" +getNodeType() + ">"; };

//! Return the xml footer for the node
std::string Node::getFooter() const { return "</" + getNodeType() + ">"; };

//! Return the id of a variable, ideally should be pure virtual
std::string Node::getId() const { return getNodeType();}

void Node::tab(bool open){
 if (open) {
   tabcount++;
 } else {
   tabcount--;
 }
 std::cout << std::string(tabcount, '\t');
}

void Node::print_c() const {
  std::cout << "// " << getNodeType() << std::endl;
}

void Node::print_xml() const {
  tab();
  std::cout << getHeader() << std::endl;
  tab_incr();
  // print_children_xml();
  tab(0);
  std::cout << getFooter() << std::endl;
};
