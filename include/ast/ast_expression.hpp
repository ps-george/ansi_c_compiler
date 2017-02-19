#ifndef AST_EXPRESSION_HPP_
#define AST_EXPRESSION_HPP_

#include "ast_node.hpp"
#include "ast_list.hpp"

//! Abstract base class for expressions
class Expression : public Node {
public:
  //virtual std::string getType() const = 0;
};

//! Points to any number of expressions separated by commas
class ExpressionList : public Expression, public List {
public:
  ExpressionList(std::vector<const Node *> _children) : List(_children) {}
};

//! Unary expression points to one thing
class UnaryExpression : public Expression {
private:
  const Expression * child;
};

class ConstantExpression : public UnaryExpression {};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {};

//! PrefixExpression
//! Referred to as UnaryExpression in the spec
//! 
class PrefixExpression : public UnaryExpression {};

//! Points to typename
class Sizeof : public UnaryExpression {};

//! AssignmentExpression has unaryExpression (left) followed by AssignmentExpression (right)

//! 
class TrinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * middle;
  const Expression * right;
};


class ConditionalExpression : public TrinaryExpression {
private:
};

class BinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * right;
};

//! CastExpression: Left is type-name, right is an expression
class CastExpression : public BinaryExpression {};
//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {};
//! LORExpression: LORExpression || LANDExpression
class LORExpression : public BinaryExpression {};

//! LANDExpression: LANDExpression || ORExpression
class LANDExpression : public BinaryExpression {};

//! ORExpression: ORExpression | ANDExpression
class ORExpression : public BinaryExpression {};

//! ANDExpression: ANDExpression & EORExpression
class ANDExpression : public BinaryExpression {};

//! EORExpression: EORExpression ^ EqExpression
class EORExpression : public BinaryExpression {};

//! EqExpression: EqExpression EqOp RelExpression
class EqExpression : public BinaryExpression {};

//! RelExpression: RelExpression RelOp ShiftExpression
class RelExpression : public BinaryExpression {};

//! ShiftExpression: ShiftExpression ShiftOp AddExpression
class ShiftExpression : public BinaryExpression {};

//! AddExpression: AddExpression + SubExpression
class AddExpression : public BinaryExpression {};

//! SubExpression: SubExpression - MulExpression
class SubExpression : public BinaryExpression {};

//! MulExpression: MulExpression * DivExpression
class MulExpression : public BinaryExpression {};

//! DivExpression: DivExpression / ModExpression
class DivExpression : public BinaryExpression {};

//! ModExpression: ModExpression % CastExpression
class ModExpression : public BinaryExpression {};

//! Primary expression points to identifier, constant, StringLiteral or (expression)
//! Is it unnecessary?
//class PrimaryExpression {};

// Primitives
class StringLiteral : public Expression {};

//! Abstract base class for constant
class Constant : public Expression {};

class FloatConstant : public Constant {};

class IntConstant : public Constant {};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {};

class CharConstant : public Constant {};


#endif
