#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <iostream>
#include <map>
#include <string>

#include "ast_leaf.hpp"

class Statement : public Leaf {

public:
  virtual ~Statement() {}
  virtual double evaluate( const std::map<std::string,double> &bindings=std::map<std::string,double>()) const =0;
};

class CompoundStatement : public Statement {
public:
  
};

class ConditionalStatement : public Statement {
public:
  
  
};

class IfStatement : public ConditionalStatement {
  
};

#endif
