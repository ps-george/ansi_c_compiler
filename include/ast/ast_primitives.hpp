#ifndef ast_primitives_hpp
#define ast_primitives_hpp

// To satisfy my linter...
#include "ast/ast_leaf.hpp"

#include <iostream>
#include <string>

class Primitive: public Leaf {
public:
  virtual std::string getType() const override = 0;
  
  virtual std::string getHeader() const override {return "<" + getType() + "\"/>";}
  
  virtual void print_xml() const override {
    tab(); 
    std::cout << getHeader() <<  "\n";
  }
  
  virtual std::vector<const Leaf *> getAllStems() const override {
    std::vector<const Leaf *> v {this};
    return v;
  }
  
  virtual const Leaf * add(const Leaf * l) const override {
    return this;
  }
  
};

class Variable: public Primitive {
private:
  std::string id;
public:
  Variable(const std::string &_id)
      : id(_id)
  {}
    
  virtual std::string getType() const override { return "Variable"; }
  
  virtual std::string getHeader() const override {return "<" + getType() + " id=\"" + id +  "\"/>";}
  
};

class Parameter: public Variable {
public:
  Parameter(const std::string &_id)
      : Variable(_id)
  {}
  virtual std::string getType() const override {
    return "Parameter";
  }
};


class Constant : public Primitive {
private:
  int value;
public:
  Constant(const std::string &_val)
      : value(std::stoi(_val))
  {}
  
  virtual std::string getType() const override {
    return "id";
  }
  
  virtual std::string getHeader() const override {return "<" + getType() + " value=\"" + std::to_string(value) +  "\"/>";}
};


#endif
