#ifndef AST_EXPRESSION_HPP_
#define AST_EXPRESSION_HPP_

#include "ast_node.hpp"
#include "ast_list.hpp"

//! Abstract base class for expressions
class Expression : public Node {
public:
  virtual ~Expression(){};
  virtual std::string getType() const { return "Expression"; };
};

class EmptyExpression : public Expression {
public:
  virtual ~EmptyExpression(){};
  virtual std::string getType() const { return "EmptyExpression"; };
  EmptyExpression(){};
};

//! Points to any number of expressions separated by commas
class ExpressionList : public List {
public:
  virtual ~ExpressionList(){};
  ExpressionList(std::vector<const Node *> _children) : List(_children) {}
};

//! Unary expression points to one thing
class UnaryExpression : public Expression {
private:
  const Node * child;
public:
  virtual ~UnaryExpression(){
    delete child;
  }
  explicit UnaryExpression(const Node * c) : child(c) {};
};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};
//
////! PrefixExpression
//class PrefixExpression : public UnaryExpression {};

class PostIncrExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};

class PostDecrExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
  
};

//! PrefixExpression
//! Referred to as UnaryExpression in the spec

class PreIncrExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};

class PreDecrExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};


//! Points to typename
class SizeofExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};

//! AssignmentExpression has unaryExpression (left) followed by AssignmentExpression (right)

//! 
class TrinaryExpression : public Expression {
private:
  const Node * left;
  const Node * middle;
  const Node * right;
public:
  ~TrinaryExpression(){
    delete left;
    delete middle;
    delete right;
  }
  
  explicit TrinaryExpression(const Node * l, const Node * m, const Node * r)
    : left(l), middle(m), right(r) {}
};


class ConditionalExpression : public TrinaryExpression {
private:
public:
  ConditionalExpression(const Node * l, const Node * m, const Node * r)
    : TrinaryExpression(l,m,r){}
};

class BinaryExpression : public Expression {
private:
  const Node * left;
  const Node * right;
public:
  explicit BinaryExpression(const Node * l,const Node * r)
    : left(l), right(r) {}
};

//! CastExpression: Left is type-name, right is an expression
class CastExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};
//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {
private:
  std::string op;
public:
  AssignmentExpression(const Node * l, const Node * r, std::string _op) : BinaryExpression(l,r), op(_op) {};
  ~AssignmentExpression(){};
  
  virtual void compile() const;
};
//! LORExpression: LORExpression || LANDExpression
class LORExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! LANDExpression: LANDExpression || ORExpression
class LANDExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! ORExpression: ORExpression | ANDExpression
class ORExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! ANDExpression: ANDExpression & EORExpression
class ANDExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! EORExpression: EORExpression ^ EqExpression
class EORExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! EqExpression: EqExpression EqOp RelExpression
class EQExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! NeExpression: EqExpression NeOp RelExpression
class NEExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! RelExpression: RelExpression RelOp ShiftExpression
//class RelExpression : public BinaryExpression {};

//! LtExpression: LtExpression < ShiftExpression
class LTExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! GtExpression: LtExpression < ShiftExpression
class GTExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! LeExpression: LtExpression < ShiftExpression
class LEExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! GeExpression: LtExpression < ShiftExpression
class GEExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! ShiftExpression: ShiftExpression ShiftOp AddExpression
//class ShiftExpression : public BinaryExpression {};

//! ShiftExpression: ShiftExpression ShiftOp AddExpression
class RRExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! ShiftExpression: ShiftExpression ShiftOp AddExpression
class LLExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! AddExpression: AddExpression + SubExpression
class AddExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! SubExpression: SubExpression - MulExpression
class SubExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! MulExpression: MulExpression * DivExpression
class MulExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! DivExpression: DivExpression / ModExpression
class DivExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! ModExpression: ModExpression % CastExpression
class ModExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};

//! Primary expression points to identifier, constant, StringLiteral or (expression)
//! Is it unnecessary?
//class PrimaryExpression {};

// Primitives
//class  : public Expression {};
//
////! Abstract base class for constant
//class Constant : public Expression {};
//
//class FloatConstant : public Constant {};
//
//class IntConstant : public Constant {};
//
////! An identifier, check identifier list for definition.
////! Enum is of type int.
//class EnumConstant : public Constant {};
//
//class CharConstant : public Constant {};

#endif
