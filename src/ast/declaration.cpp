/*
 * declaration.cpp
 *
 *
 */

#include "ast/declaration.hpp"

std::string Declarator::getNodeType() const { return "Declarator"; };
std::string InitDeclarator::getNodeType() const { return "InitDeclarator"; };
std::string ArrayDeclarator::getNodeType() const { return "ArrayDeclarator"; };
std::string FunctionDeclarator::getNodeType() const { return "FunctionDeclarator"; };
std::string Declaration::getNodeType() const { return "Declaration"; };

/*
 * PRINT_ASM
 */
// Something has been declared
void Declaration::print_asm(Context& ctxt) const{
  //! \todo What if variable has already been assigned and we want to 'shadow'
  ctxt.ss() << "# Declaration, with type '" << type->getTypename() << "' of: ";
  for (auto &it : dlist->getChildren()){
    ctxt.ss() << it->getId() << ", ";
    ctxt.assignVariable(it->getId(), type->getTypename());
  }
  ctxt.ss() << std::endl;
}

/*
 *
 * 
 */

std::vector<const Node *> InitDeclarator::getChildren() const {
  std::vector<const Node *> v = Declarator::getChildren();
  v.push_back(e);
  return v;
}

std::vector<const Node *> Declaration::getChildren () const {
  // for each item in dlist
  std::cerr << "Finding children of declaration" << std::endl;
  return dlist->getChildren();
}

void Declaration::setChildDefs() const {
  // For each of then declarators that are children of this
  for (auto &it : getChildren()){
    // Get the name of the thing being declared
    std::cerr <<  "Found declaration of: " << it->getId() << std::endl;
    childDefs.push_back(it->getId());
  }
}

std::vector<std::string> Declaration::getChildDefs() const {
 return childDefs;
}

/* PRINT XML FUNCTIONS */
void Declarator::print_xml() const{
  tab();
  child->print_xml();
}

void FunctionDeclarator::print_xml() const {
  // For each of the parameters, print out the parameter
  for (auto &it : p->getChildren()) {
    it->print_xml();
  }
};

void Declaration::print_xml() const{
  dlist->print_xml();
};


void Declarator::print_c() const{
  child->print_c();
}

void FunctionDeclarator::print_c() const {
  // For each of the parameters, print out the parameters
  // std::cout << "/* "<< getNodeType() << "*/";
  std::cout << getId() << "(";
  bool first = true;
  for (auto &it : p->getChildren()) {
    if (!first){
      std::cout << ", ";
    }
    first = false;
    it->print_c();
  }
  std::cout << ")";
};

void Declaration::print_c() const{
  tab();
  std::cout << type->getTypename() << " ";
  bool first = true;
  for (auto &it : dlist->getChildren()) {
    if (!first){
      std::cout << ", ";
    }
    first = false;
    it->print_c();
  }
  // std::cout << "/* "<< getNodeType() << "*/" << std::endl;
};
