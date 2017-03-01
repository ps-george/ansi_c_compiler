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
  virtual std::string getNodeType() const override;
  std::string getOp() const;
  virtual std::vector<const Node *> getChildren() const;
  const Expression * getLeft() const { return left;};
  const Expression * getRight()const { return right;};
  void print_c() const;
  virtual void print_asm(Context& ctxt) const override;
};


//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;
  virtual std::string getNodeType() const override;
  virtual void print_asm(Context& ctxt) const override;
};

#endif
