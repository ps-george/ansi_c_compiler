/*
 * list.cpp
 *
 *
 */

#include "tokens.hpp"
#include "ast/list.hpp"
#include "ast/declaration.hpp"
#include "ast/constant.hpp"

/*
 * GETTERS
 */

std::string List::getNodeType() const { return "List"; };
std::string TabbedList::getNodeType() const { return "Scope"; }
std::string Program::getNodeType() const { return "Program"; }
std::string DeclarationList::getNodeType() const { return "DeclarationList"; }
std::string ParameterList::getNodeType() const { return "ParameterList"; }
std::string ExpressionList::getNodeType() const { return "ExpressionList"; }

std::vector<const Node *> List::getChildren() const { 
  if (!children.size()){
    //std::cerr << "No children" << std::endl;
  }
  return children; 
};

std::vector<const Node *> ExpressionList::getChildren() const {
  return List::getChildren();
}
/*
 * END OF GETTERS
 */

/*
 *  COMMON FUNCTIONS
 */

List::~List() {
  for (auto &it : children)
    delete it;
  children.clear();
}

const Node *List::add(const Node *child) const {
  sourceline = yylsourcelino;
  sourcecol = yylcolno;
  children.push_back(child);
  return this;
};

/*
 *  END OF COMMON FUNCTIONS
 */

/*
 * PRINT ASM
 */


Context Program::print_asm(Context ctxt, int d) const {
  ctxt.ss() <<
  "\t.section .mdebug.abi32\n\t.previous\n\t.nan	legacy\n\t.module	fp=xx\n\t.module	nooddspreg\n\t.abicalls\n";
  // Assign strings
  for (auto &it: getStrings()){
    ctxt.ss() << "# string " << it << std::endl;
    ctxt.addString(it);
  }
  
  ctxt.createStrings();
  
  for (auto &it : getChildren()){
    if (it->getNodeType()=="Declaration"){
      for (auto &it1 : it->getChildren()){
        // All function declarators are globl, don't want to do it for these
        if (it1->getNodeType()!="FunctionDeclarator"){
          ctxt.ss() << "# " << it1->getNodeType() << std::endl;
          ctxt.ss() << "\t.globl\t" << it1->getId() << std::endl;
          ctxt.ss() << "\t.data" << std::endl;
          ctxt.ss() << "\t.align\t2" << std::endl;
          ctxt.ss() << "\t.type\t" << it1->getId() << ",\t@object" <<std::endl;
          ctxt.ss() << "\t.size\t" << it1->getId() << ",\t4" <<std::endl;
          ctxt.ss() << it->getId() << ":" << std::endl;
          // SO UGLY
          if (it1->getNodeType()=="InitDeclarator")
            ctxt.ss() << "\t.word\t" << ((const Constant *)(((const InitDeclarator *)it1)->getChildren().back()))->getValue() << std::endl;
        }
        //else {
        ctxt.assignVariable(it->getId(), ((const Declaration * )it)->getTypename(),true);
        //}
      }
    }
  }
  
  ctxt.ss() << "\t.text\n";
  for (auto &it : getChildren()){
    if (it->getNodeType()!="Declaration"){
      ctxt = it->print_asm(ctxt, d);
    }
  }
  return ctxt;
}

//! Need to override this because it's an ambiguous base
Context ExpressionList::print_asm(Context ctxt, int d) const{
  //ctxt.ss() << "# print asm for " << getNodeType() << "'s children" << std::endl;
  for (auto &it : List::getChildren()){
    // ctxt.ss() << "# " << it->getNodeType() << std::endl;
    it->print_asm(ctxt,d);
  }
  return ctxt;
} //! Print out mips assembly

/*
 *  PRINT XML
 */

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

/*
 * END OF PRINT XML
 */

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
