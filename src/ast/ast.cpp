/*
 * ast.cpp
 *
 *
 */

#include "ast.hpp"

void AssignmentExpression::compile() const{
  if (op=="="){
   
  }else if (op=="*="){
   
  }else if (op=="/="){
   
  }else if (op=="%="){
   
  }else if (op=="+="){
   
  }else if (op=="-="){
   
  }else if (op=="&="){
   
  }else if (op=="|="){
   
  }else if (op=="^="){
   
  }else if (op=="<<="){
   
  }else if (op==">>="){
   
  }else {
   throw std::runtime_error("Unknown construct '" + op + "'");
  }
 }
