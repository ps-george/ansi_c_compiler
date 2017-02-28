/*
 * node.cpp
 *
 *
 */

#include "ast/node.hpp"

std::string Node::getNodeType() const {
  return "Node";
}

//! Return the xml header for the node
std::string Node::getHeader() const { return "<" +getNodeType() + ">"; };

//! Return the xml footer for the node
std::string Node::getFooter() const { return "</" + getNodeType() + ">"; };

//! Return the id of a variable, ideally should be pure virtual
std::string Node::getId() const { return getNodeType();}

//! Populate metadata vectors with the declarations held by the children
void Node::getChildDefs() const {
  // Get all the children
  for (auto &it : getChildren()){
  // For each of the children, get the result of their getChildDefs and apppend them together
  }

}

void Node::tab(bool open){
 if (open) {
   tabcount++;
 } else {
   tabcount--;
 }
 std::cout << std::string(tabcount, '\t');
}

void Node::print_asm(Context& ctxt) const {
  ctxt.ss() << "# " << getNodeType() << " not implemented yet" << std::endl;
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
