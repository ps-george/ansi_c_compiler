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

  virtual std::string getNodeType() const override;

  virtual std::string getValue() const { return valstr; };
  virtual std::string getHeader() const override {
    return "<" + getNodeType() + " value=\"" + valstr + "\" " + getDeets() + " />";
  }
  
  virtual std::vector<const Node *> getChildren() const override {return {};}
  // virtual void print_c() const override;
  virtual Context print_asm(Context ctxt) const override; 
  virtual void print_xml(std::ostream &stream) const override;
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
  DoubleConstant(const std::string &_valstr);
  virtual std::string getNodeType() const override;
};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {
  virtual ~EnumConstant(){};
  virtual std::string getNodeType() const override;
};

class CharConstant : public Constant {
private:
  char val;
public:
  virtual ~CharConstant(){};
  CharConstant(const std::string &_valstr);;
  virtual std::string getNodeType() const override;
};

#endif
