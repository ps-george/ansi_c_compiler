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
  bool first = true;
  for (auto &it : p->getChildren()) {
    if (!first)
      std::cout << ", ";
    it->print_c();
  }
};
