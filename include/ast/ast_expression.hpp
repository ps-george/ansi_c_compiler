#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <iostream>
#include <map>
#include <string>

#include "ast_leaf.hpp"

class Expression : public Leaf {

public:
  virtual ~Expression() {}
  virtual double evaluate( const std::map<std::string,double> &bindings=std::map<std::string,double>()) const =0;
};

#endif
