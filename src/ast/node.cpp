/*
 * node.cpp
 *
 *
 */

#include "ast/node.hpp"
#include "tokens.hpp"

Node::Node() : sourceline(yylsourcelino), sourcecol(yylcolno) {};

std::string Node::getNodeType() const {
  return "Node";
}

std::string Node::getDeets() const { 
  std::string defs = " childDefs=";
  if (childDefs.size()){
    for (auto &it : childDefs){
      defs += it + " ";
    }
  }
  else {
    defs = "";
  }
  return "line=" + std::to_string(sourceline) + " col=" + std::to_string(sourcecol) + defs;
}

//! Return the xml header for the node
std::string Node::getHeader() const { return "<" + getNodeType() + " " + getDeets() + ">"; };

//! Return the xml footer for the node
std::string Node::getFooter() const { return "</" + getNodeType() + ">"; };

//! Return the id of a variable, ideally should be pure virtual
std::string Node::getId() const { return getNodeType();}

//! Populate metadata vectors with the declarations held by the children
void Node::setChildDefs() const {
  // Get all the children
  for (auto &it : getChildren()){
    it->setChildDefs();
    std::vector<std::string> tmp = it->getChildDefs(); // Sets the metadata by getting the childDefs of it's children
    childDefs.insert(childDefs.end(), tmp.begin(), tmp.end());
  }
}

//! Populate metadata vectors with the declarations held by the children
std::vector<std::string> Node::getChildDefs() const {
  return childDefs;
}

void Node::tab(std::ostream &stream, bool open){
 if (open) {
   tabcount++;
 } else {
   tabcount--;
 }
 stream << std::string(tabcount, '\t');
}

void Node::print_asm(Context& ctxt) const {
  //ctxt.ss() << "# printing asm for " << getNodeType() << std::endl;
  for (auto &it : getChildren()){
    //ctxt.ss() << "# child is " << it->getNodeType() << std::endl;
    it->print_asm(ctxt);
  }
  // ctxt.ss() << "# " << getNodeType() << " not implemented yet" << std::endl;
}

// void Node::print_c() const { 
//  std::cout << "// " << getNodeType() << std::endl;
//}

void Node::print_xml(std::ostream &stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
  tab_incr();
  for (auto &it : getChildren()){
    it->print_xml(stream);
  }
  tab_decr();
  tab(stream);
  stream << getFooter() << std::endl;
};
