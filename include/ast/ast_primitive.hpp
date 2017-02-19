#ifndef AST_PRIMITIVE_HPP_
#define AST_PRIMITIVE_HPP_

#include "ast_node.hpp"
#include "ast_list.hpp"
#include "ast_expression.hpp"

// Primitives

class Primitive: public Expression {
public:
  virtual ~Primitive(){};
  
  virtual std::string getType() const override = 0;
  
  virtual std::string getHeader() const override {return "<" + getType() + "\" />";}
  
  virtual void print_xml() const override {
    tab(); 
    std::cout << getHeader() <<  "\n";
  }
  
};

//! Abstract base class for constant
class Constant : public Primitive {
private:
  std::string valstr;
public:
  virtual ~Constant(){};
  explicit Constant(const std::string &_valstr) : valstr(_valstr){};
  
  virtual std::string getType() const override {
    return "Constant";
  }
  virtual std::string getHeader() const override {return "<" + getType() + " value=\"" + valstr +  "\" />";}
};

class StringLiteral : public Constant {
public:
  virtual ~StringLiteral(){};
  using Constant::Constant;
  std::string getType() const override { return "StringLiteral"; };
};

class FloatConstant : public Constant {
private:
  float val;
public:
  virtual ~FloatConstant(){};
  
  
  FloatConstant(const std::string &_valstr) : Constant(_valstr){
    val = std::stof(_valstr);
  };
  
  virtual std::string getType() const override {
    return "Float";
  }
};

class DoubleConstant : public Constant {
private:
  double val;
public:
  virtual ~DoubleConstant(){};
  
  DoubleConstant(const std::string &_valstr) : Constant(_valstr){
    val = std::stod(_valstr);
  };
  
  virtual std::string getType() const override {
    return "Double";
  }
  
};

class IntConstant : public Constant {
private:
  int val;
public:
  virtual ~IntConstant(){};
  
  IntConstant(const std::string &_valstr) : Constant(_valstr){
    val = std::stoi(_valstr);
  };
  
  virtual std::string getType() const override {
    return "Int";
  }
};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {
  virtual ~EnumConstant(){};
};

class CharConstant : public Constant {
  virtual ~CharConstant(){};
};


class Variable: public Primitive {
private:
  std::string id;
public:
  virtual ~Variable(){};
  
  Variable(const std::string &_id) : id(_id){};
    
  virtual std::string getType() const override { return "Variable"; }
  
  virtual std::string getHeader() const override {return "<" + getType() + " id=\"" + id +  "\" />";}
  
};

class Parameter: public Variable {
public:
  virtual ~Parameter(){};
  Parameter(const std::string &_id) : Variable(_id){}
  
  virtual std::string getType() const override {
    return "Parameter";
  }
};


#endif
