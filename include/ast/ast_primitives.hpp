#ifndef ast_primitives_hpp
#define ast_primitives_hpp

// To satisfy my linter...
#include "ast/ast_expression.hpp"

#include <iostream>
#include <string>

class Variable : public Leaf {
private:
  std::string id;
public:
  Variable(const std::string &_id)
      : id(_id)
  {}
  std::string getId() const { return id; }
  
  virtual std::string getType() const override { return "Variable"; }
  
  virtual void print_xml() const override {
    std::cout << "<" << getType() <<" id=\"" << id << "\"/>\n";
  }
  
  virtual std::vector<const Leaf *> getAllStems() const override {
    std::vector<const Leaf *> v {this};
    return v;
  }
  
  virtual const Leaf * add(const Leaf * l) const override {
    return this;
  }
  
};

class Parameter: public Variable {
private:
  std::string id;

public:
  Parameter(const std::string &_id)
      : Variable(_id)
  {}
  virtual std::string getType() const override {
    return "Parameter";
  }
};

#endif
