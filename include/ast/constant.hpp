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
  Constant(const std::string &_valstr);

  virtual std::string getNodeType() const;

  virtual std::string getValue() const { return valstr; };
  virtual std::string getHeader() const {
    return "<" + getNodeType() + " value=\"" + valstr + "\" />";
  }
  
  virtual std::vector<const Node *> getChildren() const {return {this};}
  virtual void print_c() const;
};

class StringLiteral : public Constant {
public:
  virtual ~StringLiteral(){};
  using Constant::Constant;
  std::string getNodeType() const override;
};

class IntConstant : public Constant {
private:
  int val;

public:
  virtual ~IntConstant(){};
  IntConstant(const std::string &_valstr);
  virtual std::string getNodeType() const override;
};

class FloatConstant : public Constant {
private:
  float val;
public:
  virtual ~FloatConstant(){};
  FloatConstant(const std::string &_valstr);

  virtual std::string getNodeType() const override;
};

class DoubleConstant : public Constant {
private:
  double val;
public:
  virtual ~DoubleConstant(){};
  DoubleConstant(const std::string &_valstr);;
  virtual std::string getNodeType() const override;
};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {
  virtual ~EnumConstant(){};
  virtual std::string getNodeType() const override;
};

class CharConstant : public Constant {
  virtual ~CharConstant(){};
  virtual std::string getNodeType() const override;
};

#endif
