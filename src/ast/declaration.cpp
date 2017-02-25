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
  std::cout << "/* "<< getNodeType() << "*/";
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
