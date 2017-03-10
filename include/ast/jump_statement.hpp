#ifndef JUMP_STATEMENT_HPP_
#define JUMP_STATEMENT_HPP_

#include "statement.hpp"

/*! \brief JumpStatement
 *
 * A jump statement causes an unconditional jump to another place
 */
class JumpStatement : public Statement {
public:
  JumpStatement(){};
  virtual ~JumpStatement(){};
  virtual std::string getNodeType() const override;
  virtual void print_xml(std::ostream& stream) const override;
  //virtual void print_asm(Context ctxt, int vars) const;
};
/*!
Constraints

The identifier in a goto statement shall name a label located somewhere in the
current function.

Semantics

A goto statement causes an unconditional jump to the statement prefixed by the
named label in the current function.
 */
class GotoStatement : public JumpStatement {
private:
  std::string label;

public:
  GotoStatement(const std::string l) : label(l){};
  virtual ~GotoStatement(){};
  virtual std::string getNodeType() const override;
};

/*!
 * Constraints

A continue statement shall appear only in or as a loop body.

Semantics

A continue statement causes a jump to the loop-continuation portion of the
smallest enclosing iteration statement; that is, to the end of the loop body.
More precisely, in each of the statements
 */
class ContinueStatement : public JumpStatement {
public:
  ContinueStatement(){};
  virtual ~ContinueStatement(){};
  virtual std::string getNodeType() const override;
};

/*! \brief BreakStatement
 * Constraints
A break statement shall appear only in or as a switch body or loop body.

Semantics
A break statement terminates execution of the smallest enclosing switch or
iteration statement.
 */
class BreakStatement : public JumpStatement {
public:
  BreakStatement(){};
  virtual ~BreakStatement(){};
  virtual std::string getNodeType() const override;
};

/*!
 *
Constraints

A return statement with an expression shall not appear in a function whose
return type is void .

Semantics
A return statement terminates execution of the current function and returns
control to its caller. A function may have any number of return statements, with
and without expressions.

If a return statement with an expression is executed, the value of the
expression is returned to the caller as the value of the function call
expression. If the expression has a type different from that of the function in
which it appears, it is converted as if it were assigned to an object of that
type.

If a return statement without an expression is executed, and the value of the
function call is used by the caller, the behavior is undefined. Reaching the }
that terminates a function is equivalent to executing a return statement without
an expression.
 */
class ReturnStatement : public JumpStatement {
private:
  const ExpressionStatement *expr;

public:
  ReturnStatement(const ExpressionStatement *e) : expr(e){};
  virtual std::string getNodeType() const override;
  virtual std::vector<const Node *> getChildren() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};

#endif
