#ifndef UNARY_EXPRESSION_HPP_
#define UNARY_EXPRESSION_HPP_

#include "list.hpp"

//! Unary expression points to one thing
class UnaryExpression : public Expression {
protected:
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
  virtual std::vector<const Node *> getChildren() const override { return {child};}
  virtual std::string getNodeType() const override;
  // virtual void print_c() const;
};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {
public:
  PostfixExpression(const Expression * c, std::string* _op) : UnaryExpression(c,_op) {};
  PostfixExpression(const Expression * c) : UnaryExpression(c) {};
  virtual std::string getNodeType() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};



//! PostfixExpression
class PrefixExpression : public UnaryExpression {
public:
  PrefixExpression(const Expression * c, std::string* _op) : UnaryExpression(c,_op) {};
  PrefixExpression(const Expression * c) : UnaryExpression(c) {};
  virtual std::string getNodeType() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};

class CastExpression : public PrefixExpression {
public:
  CastExpression(const Expression * c, std::string* _op) : PrefixExpression(c,_op) {};
  virtual std::string getNodeType() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};

//! Function call
class FunctionCall : public PostfixExpression {
private:
  const ExpressionList * args;
public:
  FunctionCall(const Expression * _expr) : PostfixExpression(_expr), args(new ExpressionList({})) {};
  FunctionCall(const Expression * _expr, const List * _args) : PostfixExpression(_expr), args((const ExpressionList *)_args) {};
  virtual std::string getNodeType() const override;
  virtual std::string getId() const { return child->getId(); };
  virtual Context print_asm(Context ctxt, int d = 2) const override;
  virtual void setParamUses() const override;
};

//! Array access
class SquareOperator : public PostfixExpression {
private:
  const Expression * arg;
public:
  SquareOperator(const Expression * _expr) : PostfixExpression(_expr) {};
  SquareOperator(const Expression * _expr, const Expression * _arg) : PostfixExpression(_expr), arg(_arg) {};
  virtual Context print_asm(Context ctxt, int d = 2) const override;
  virtual std::string getNodeType() const override { return "SquareOperator";} ;
  virtual std::vector<const Node *> getChildren() const override { return {child,arg};}
  virtual std::string getId() const override { return child->getId(); };
};

//! Dot and arrow operators
class StructOperator : public PostfixExpression {
private:
  std::string id;
public:
  StructOperator(const Expression * _expr, std::string *_id) : PostfixExpression(_expr), id(*_id) {};
};

//! Dot operator
class DotOperator : public StructOperator {
public:
  DotOperator(const Expression * _expr, std::string *_id) : StructOperator(_expr,_id) {};
};

//! Arrow (pointer) operator
class ArrowOperator : public StructOperator {
public:
  ArrowOperator(const Expression * _expr, std::string *_id) : StructOperator(_expr,_id) {};
};


#endif
