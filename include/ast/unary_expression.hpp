#ifndef UNARY_EXPRESSION_HPP_
#define UNARY_EXPRESSION_HPP_

#include "expression.hpp"

//! Unary expression points to one thing
class UnaryExpression : public Expression {
private:
  const Expression * child;
  std::string op;
public:
  virtual ~UnaryExpression(){
    delete child;
  }
  UnaryExpression(const Expression * c, std::string* _op) : child(c), op(*_op) {};
  UnaryExpression(const Expression * c) : child(c) {
    op = "";
  };
  virtual void print_c() const;
};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {
public:
  PostfixExpression(const Expression * c, std::string* _op) : UnaryExpression(c,_op) {};
  PostfixExpression(const Expression * c) : UnaryExpression(c) {};
};

//! PostfixExpression
class PrefixExpression : public UnaryExpression {
public:
  PrefixExpression(const Expression * c, std::string* _op) : UnaryExpression(c,_op) {};
  PrefixExpression(const Expression * c) : UnaryExpression(c) {};
};

#endif
