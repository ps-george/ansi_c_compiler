#ifndef CONSTANT_HPP_
#define CONSTANT_HPP_

#include "expression.hpp"

//! Abstract base class for constant
class Constant : public Expression {
private:
  std::string valstr;
  // Constant will have a type as well`
public:
  virtual ~Constant(){};
  Constant(const std::string &_valstr) : valstr(_valstr){};

  virtual std::string getNodeType() const { return "Constant"; }

  virtual std::string getValue() const { return valstr; };
  virtual std::string getHeader() const {
    return "<" + getNodeType() + " value=\"" + valstr + "\" />";
  }
  virtual void print_c() const;
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

#endif
