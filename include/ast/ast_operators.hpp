#ifndef ast_operators_hpp
#define ast_operators_hpp

// To satisfy my linter...
#include "ast/ast_expression.hpp"

#include <iostream>
#include <string>
class Operator : public Expression {
private:
  const Expression *left;
  const Expression *right;

protected:
  Operator(const Expression *_left, const Expression *_right)
      : left(_left), right(_right) {}

public:
  virtual ~Operator() {
    delete left;
    delete right;
  }

  virtual const char *getOpcode() const = 0;

  const Expression *getLeft() const { return left; }

  const Expression *getRight() const { return right; }

  virtual void print_xml() const override {
    std::cout << "<Operator id =\"" << getOpcode() << "\">\n";
    this->tab(true);
    std::cout << "<Left pid =\"" << getOpcode() << "\">\n";
    this->tab(true);
    left->print_xml();
    this->tab(false);
    std::cout << "</Left>\n";
    this->tab();
    std::cout << "<Right pid =\"" << getOpcode() << "\">\n";
    this->tab(true);
    right->print_xml();
    this->tab(false);
    std::cout << "</Right>\n";
    this->tab(false);
    std::cout << "</Operator>\n";
  }
};

class AddOperator : public Operator {
protected:
  virtual const char *getOpcode() const override { return "+"; }

public:
  AddOperator(const Expression *_left, const Expression *_right)
      : Operator(_left, _right) {}
};

class SubOperator : public Operator {
protected:
  virtual const char *getOpcode() const override { return "-"; }

public:
  SubOperator(const Expression *_left, const Expression *_right)
      : Operator(_left, _right) {}
};

class MulOperator : public Operator {
protected:
  virtual const char *getOpcode() const override { return "*"; }

public:
  MulOperator(const Expression *_left, const Expression *_right)
      : Operator(_left, _right) {}
};

class DivOperator : public Operator {
protected:
  virtual const char *getOpcode() const override { return "/"; }

public:
  DivOperator(const Expression *_left, const Expression *_right)
      : Operator(_left, _right) {}
};

#endif
