/*
 * type.cpp
 *
 *
 */


#include "ast/type.hpp"

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
    ss << i->getName();
  }
  return ss.str(); 
}
