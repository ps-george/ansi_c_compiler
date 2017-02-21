#ifndef AST_PRIMITIVE_HPP_
#define AST_PRIMITIVE_HPP_

#include "ast_expression.hpp"
#include "ast_list.hpp"
#include "ast_node.hpp"

// Primitives

class Primitive : public Expression {
public:
  virtual ~Primitive(){};

  virtual std::string getNodeType() const override = 0;

  virtual std::string getHeader() const override {
    return "<" + getNodeType() + "\" />";
  }

  virtual void print_xml() const override {
    tab();
    std::cout << getHeader() << "\n";
  }
};

//! Abstract base class for constant
class Constant : public Primitive {
private:
  std::string valstr;
// Constant will have a type as well`
public:
  virtual ~Constant(){};
  explicit Constant(const std::string &_valstr) : valstr(_valstr){};

  virtual std::string getNodeType() const override { return "Constant"; }
  
  virtual std::string getValue() const { return valstr; };
  virtual std::string getHeader() const override {
    return "<" + getNodeType() + " value=\"" + valstr + "\" />";
  }
  virtual void print_cpp() const override;
};

class StringLiteral : public Constant {
public:
  virtual ~StringLiteral(){};
  using Constant::Constant;
  std::string getNodeType() const override { return "StringLiteral"; };
};

class FloatConstant : public Constant {
private:
  float val;

public:
  virtual ~FloatConstant(){};

  FloatConstant(const std::string &_valstr) : Constant(_valstr) {
    val = std::stof(_valstr);
  };

  virtual std::string getNodeType() const override { return "float"; }
};

class DoubleConstant : public Constant {
private:
  double val;

public:
  virtual ~DoubleConstant(){};

  DoubleConstant(const std::string &_valstr) : Constant(_valstr) {
    val = std::stod(_valstr);
  };

  virtual std::string getNodeType() const override { return "double"; }
};

class IntConstant : public Constant {
private:
  int val;

public:
  virtual ~IntConstant(){};
  IntConstant(const std::string &_valstr) : Constant(_valstr) {
    val = std::stoi(_valstr);
  };

  virtual std::string getNodeType() const override { return "int"; }
};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {
  virtual ~EnumConstant(){};
};

class CharConstant : public Constant {
  virtual ~CharConstant(){};
};

class Variable : public Primitive {
private:
  std::string id;
  // Variable will have a type
public:
  virtual ~Variable(){};

  Variable(const std::string &_id) : id(_id){};

  virtual std::string getNodeType() const override { return "Variable"; }

  virtual std::string getHeader() const override {
    return "<" + getNodeType() + " id=\"" + id + "\" />";
  }
};

class Parameter : public Variable {
public:
  virtual ~Parameter(){};
  Parameter(const std::string &_id) : Variable(_id) {}

  virtual std::string getNodeType() const override { return "Parameter"; }
};

#endif
