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

//! Points to any number of expressions separated by commas
class ExpressionList : public List {
public:
  virtual ~ExpressionList(){};
  ExpressionList(std::vector<const Node *> _children) : List(_children) {}
};

//! Unary expression points to one thing
class UnaryExpression : public Expression {
private:
  const Expression * child;
public:
  virtual ~UnaryExpression(){
    delete child;
  }
  explicit UnaryExpression(const Expression * c) : child(c) {};
};

class ConstantExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;
};

//! PrefixExpression
class PrefixExpression : public UnaryExpression {};

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
  const Expression * left;
  const Expression * middle;
  const Expression * right;
public:
  ~TrinaryExpression(){
    delete left;
    delete middle;
    delete right;
  }
  
  TrinaryExpression(const Expression * l, const Expression * m, const Expression * r)
    : left(l), middle(m), right(r) {}
};


class ConditionalExpression : public TrinaryExpression {
private:
public:
  ConditionalExpression(const Expression * l, const Expression * m, const Expression * r)
    : TrinaryExpression(l,m,r){}
};

class BinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * right;
public:
  explicit BinaryExpression(const Expression * l,const Expression * r)
    : left(l), right(r) {}
};

//! CastExpression: Left is type-name, right is an expression
class CastExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
};
//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {
  using BinaryExpression::BinaryExpression;
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
