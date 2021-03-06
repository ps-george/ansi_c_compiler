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
  virtual std::vector<std::string> getTypeVec() const override;
  virtual std::string getNodeType() const override;
  virtual std::string getDeets() const override;
  std::string getOp() const;
  virtual std::vector<const Node *> getChildren() const;
  const Expression * getLeft() const { return left;};
  const Expression * getRight()const { return right;};
  virtual Context print_asm(Context ctxt, int d = 2) const override;
  virtual void print_xml(std::ostream& stream) const override;
};


//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;
  virtual std::string getNodeType() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};

#endif
