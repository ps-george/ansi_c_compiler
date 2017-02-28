#ifndef BINARY_EXPRESSION_HPP_
#define BINARY_EXPRESSION_HPP_

#include "expression.hpp"

class BinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * right;
protected:
  std::string op;
public:
  BinaryExpression(const Expression * l, const Expression * r, std::string * _op);
  std::string getOp() const;
  virtual std::vector<const Node *> getChildren() const;
  void print_c() const;
  virtual void print_asm(Context& ctxt) const;
};


//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;
  virtual void print_asm(Context& ctxt) const;
};

#endif
