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
  std::cout << "<Variable id=\"" << getId() << "\" />" << std::endl;
}

void FunctionDeclarator::print_xml() const {
  for (auto &it : p->getChildren()) {
    tab();
    std::cout << "<Parameter id=\"" << it->getId() << "\" />" << std::endl;
  }
};

void Declaration::print_xml() const{
  dlist->print_xml();
};
