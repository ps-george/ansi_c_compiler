/*
 * declaration.cpp
 *
 *
 */

#include "ast/declaration.hpp"


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
