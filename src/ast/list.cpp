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
std::string ExpressionList::getNodeType() const { return "ExpressionList"; }

void ExpressionList::print_asm(Context& ctxt) const{
  ctxt.ss() << "# printing asm for " << getNodeType() << std::endl;
  for (auto &it : List::getChildren()){
    ctxt.ss() << "# child is " << it->getNodeType() << std::endl;
    it->print_asm(ctxt);
  }
} //! Print out mips assembly

/* COMMON FUNCTIONS */
std::vector<const Node *> List::getChildren() const { 
  if (!children.size()){
    //std::cerr << "No children" << std::endl;
  }
  return children; 
};

List::~List() {
  for (auto &it : children)
    delete it;
  children.clear();
}

const Node *List::add(const Node *child) const {
  children.push_back(child);
  return this;
};

/* END OF COMMON FUNCTIONS */

/* PRINT XML */

void List::print_xml(std::ostream &stream) const {
  for (auto &it : getChildren()){
    it->print_xml(stream);
  }
}

void TabbedList::print_xml(std::ostream &stream) const {
  if (getChildren().size() != 0) {
    tab(stream);
    stream << getHeader() << std::endl;
    tab_incr();
    // Print out all children on the same level -> Using list to store lots
    // lists of things
    for (auto &it : getChildren()){
      it->print_xml(stream);
    }
    tab(stream,false);
    stream << getFooter() << std::endl;
  } else {
    tab_decr();
  }
}

void DeclarationList::print_xml(std::ostream &stream) const{
  List::print_xml(stream);
};

void ExpressionList::print_xml(std::ostream &stream) const{
  List::print_xml(stream);
};

void ParameterList::print_xml(std::ostream &stream) const{
  for (auto &it : getChildren()) {
    stream << "<Parameter id=\"" << it->getId() << "\" />" << std::endl;
  }
};

/* PRINT C */

// void List::print_c() const { 
//  for (auto &it : getChildren()){
//    it->print_c();
//  }
//}

//void Program::print_c() const {
//  if (getChildren().size() != 0) {
//    //tab_incr();
//    // Print out all children on the same level -> Using list to store lots
//    // lists of things
//    for (auto &it : getChildren()) {
//      it->print_c();
//      std::cout << ';' <<std::endl;
//    } 
//  }
//}
