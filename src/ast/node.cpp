/*
 * node.cpp
 *
 *
 */

#include "ast/node.hpp"
#include "tokens.hpp"
#include "ast/jump_statement.hpp"

Node::Node() : sourceline(yylsourcelino), sourcecol(yylcolno) {};

/*
 * GETTERS
 */

std::string Node::getNodeType() const {
  return "Node";
}

//! Return the xml header for the node
std::string Node::getHeader() const { return "<" + getNodeType() + " " + getDeets() + ">"; };

//! Return the xml footer for the node
std::string Node::getFooter() const { return "</" + getNodeType() + ">"; };

//! Return the id of a variable, ideally should be pure virtual
std::string Node::getId() const { return getNodeType();}

//! Populate metadata vectors with the declarations held by the children
std::vector<std::string> Node::getChildDefs() const {
  return childDefs;
}

std::string Node::getDeets() const { 
  std::string defs = " childDefs=\"";
  if (childDefs.size()){
    for (auto &it : childDefs){
      defs += it + ",";
    }
    // Get rid of trailing comma
    defs = defs.substr(0, defs.size()-1);
    defs += "\"";
  }
  else {
    defs = "";
  }
  return "endline=\"" + std::to_string(sourceline) + "\" endcol=\"" + std::to_string(sourcecol) + "\"" + defs;
}

/*
 * SETTERS
 */

//! Populate metadata vectors with the declarations held by the children
void Node::setChildDefs() const {
  // Get all the children
  for (auto &it : getChildren()){
    it->setChildDefs();
    std::vector<std::string> tmp = it->getChildDefs(); // Sets the metadata by getting the childDefs of it's children
    childDefs.insert(childDefs.end(), tmp.begin(), tmp.end());
  }
}

void Node::tab(std::ostream &stream, bool open){
 if (!open) {
   tabcount--;
   stream << std::string(tabcount, '\t');
 } else {
   stream << std::string(tabcount, '\t');
   tabcount++;
 }
}

/*
 * PRINTERS
 */

Context Node::print_asm(Context ctxt) const {
  //ctxt.ss() << "# print asm for " << getNodeType() << "'s children" << std::endl;
  for (auto &it : getChildren()){
    //ctxt.ss() << "# hi " << it->getNodeType() << std::endl;
    // If we are passing by value, siblings aren't away of context changes
    ctxt = it->print_asm(ctxt);
  }
  return ctxt;
  // ctxt.ss() << "# " << getNodeType() << " not implemented yet" << std::endl;
}

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
