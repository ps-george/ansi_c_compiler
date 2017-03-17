/*
 * type.cpp
 *
 *
 */


#include "ast/type.hpp"

/* GETTERS */
std::string TypeSpecifier::getName() const {
  return name;
}

std::string Type::getTypename() const { 
  std::stringstream ss; 
  bool first = true;
  for (auto i: type_specifiers){
    if (!first){
      ss << " ";
    }
    first = false;
    ss << i->getName();
  }
  return ss.str(); 
}

/* END OF GETTERS */

void Type::setPtr() const {
  ptr = true;
}
