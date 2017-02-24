#ifndef AST_EXPRESSION_HPP_
#define AST_EXPRESSION_HPP_

#include "ast_node.hpp"
#include "ast_list.hpp"

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

//! Points to any number of expressions separated by commas
class ExpressionList : public Expression, public List {
  //! Contains a vector of pointers to ast nodes
public:
  virtual ~ExpressionList(){};
  ExpressionList(std::vector<const Node *> _children) : List(_children) {}
/*
protected:
  mutable std::vector<const Expression *> children;
public:
  //! Initialise using brace initializer new List({arg1, arg2, arg3})
  ExpressionList(std::vector<const Expression *> _children) : children(_children) {}
  //! Destructor for list
  virtual ~ExpressionList(){};
  
  virtual std::string getNodeType() const { return "List"; };
  
  virtual std::vector<const Expression *> getChildren() const { return children; };
  
  // Print out all children on the same level -> Using list to store lists of things
  virtual void print_xml() const { print_children_xml(); }
  
  virtual void print_children_xml() const {};
  
  // Add a child
  virtual const ExpressionList * add(const Expression * child) const;
  */
};

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
  virtual void print_cpp() const;
};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {
public:
  PostfixExpression(const Expression * c, std::string* _op) : UnaryExpression(c,_op) {};
  PostfixExpression(const Expression * c) : UnaryExpression(c) {};
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
  
  virtual void print_cpp() const;
  TrinaryExpression(const Expression * l, const Expression * m, const Expression * r)
    : left(l), middle(m), right(r) {}
};

class BinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * right;
protected:
  std::string op;
public:
  BinaryExpression(const Expression * l, const Expression * r, std::string * _op)
    : left(l), right(r), op(*_op) {}
  std::string getOp() const { return op; };
  void print_cpp() const;
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
