#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include "node.hpp"

/*!
 * \brief Statement
 *
 * Can be LabeledStatement, CompoundStatement, ExpressionStatement,
 * SelectionStatement, IterationStatement, JumpStatement
 */
class Statement : public Node {
public:
  virtual ~Statement(){};
  virtual std::string getNodeType() const = 0;
  // virtual void print_c() const;
};

//! Abstract base class for expressions
class Expression : public Node {
public:
  virtual ~Expression(){};
  virtual std::string getNodeType() const =0;
  virtual std::vector<std::string> getTypeVec() const { return std::vector<std::string>{"Int","0x0","0x0","Signed"}; };
  virtual std::string getId() const { return "No id"; }
  virtual const Expression * add(const Expression * child) const {(void)child; return this;};
  virtual void print_xml(std::ostream& stream) const override;
};

class EmptyExpression : public Expression {
public:
  virtual ~EmptyExpression(){};
  virtual std::string getNodeType() const override;
  EmptyExpression(){};
  virtual std::vector<const Node *> getChildren() const override { return {}; }
};

//! 
class TrinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * middle;
  const Expression * right;
public:
  ~TrinaryExpression(){
    delete left;
    delete middle;
    delete right;
  }
  virtual std::string getNodeType() const override;
  // virtual void print_c() const override;
  TrinaryExpression(const Expression * l, const Expression * m, const Expression * r)
    : left(l), middle(m), right(r) {}
  virtual std::vector<const Node *> getChildren() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};

//! Primary expression points to identifier, constant, StringLiteral or (expression)
//! Is it unnecessary?
//class PrimaryExpression {};

#endif
