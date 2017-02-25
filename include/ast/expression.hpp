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
  virtual std::string getNodeType() const { return "Statement"; };
};

//! Abstract base class for expressions
class Expression : public Statement {
public:
  virtual ~Expression(){};
  virtual std::string getNodeType() const { return "Expression"; };
  virtual const Expression * add(const Expression * child) const {(void)child; return this;};
  
};

class EmptyExpression : public Expression {
public:
  virtual ~EmptyExpression(){};
  virtual std::string getNodeType() const { return "EmptyExpression"; };
  EmptyExpression(){};
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
  
  virtual void print_c() const;
  TrinaryExpression(const Expression * l, const Expression * m, const Expression * r)
    : left(l), middle(m), right(r) {}
};

//! Primary expression points to identifier, constant, StringLiteral or (expression)
//! Is it unnecessary?
//class PrimaryExpression {};

#endif
