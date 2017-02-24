#ifndef AST_STATEMENT_HPP
#define AST_STATEMENT_HPP

#include "ast_expression.hpp"
#include "ast_list.hpp"
#include "ast_node.hpp"
#include "ast_declaration.hpp"

//! An expression evaluated as void for its side-effects
class ExpressionStatement : public Statement {
private:
  const Expression *expr;
public:
  ExpressionStatement(const Expression *e) : expr(e){};
  ~ExpressionStatement(){};
};

/*!
 * \brief ConditionalStatement (can be Selection or Iteration)
 *
 * Has an Expression as the condition, Statement as result
 */
class ConditionalStatement : public Statement {
protected:
  const Expression *cond;
  const Statement *stat1;

public:
  virtual ~ConditionalStatement() {
    delete cond;
    delete stat1;
  };
  //! Constructor with Expression and Statement
  ConditionalStatement(const Expression *c, const Statement *s)
      : cond(c), stat1(s) {}
  virtual std::string getNodeType() const { return "ConditionalStatement"; };
  virtual void print_xml() const;
  virtual const Expression *getCondition() const { return cond; };
  virtual const Statement *getBody() const { return stat1; };
};

/*!
 * \brief IterationStatement
 *
 * Has an Expression as the condition, Statement as iterated body
 */
class IterationStatement : public ConditionalStatement {
public:
  virtual ~IterationStatement(){};
  virtual std::string getNodeType() const { return "IterationStatement"; };
  virtual void print_cpp() const {
    // while ()
    std::cout << getNodeType() << " (";
    getCondition()->print_cpp();
    std::cout << ")\n";
    tab();
    getBody()->print_cpp();  
  };
  IterationStatement(const Expression *c, const Statement *s)
      : ConditionalStatement(c, s) {}
};

/*!
 * \brief WhileStatement
 *
 * Has an Expression as the condition, Statement as iterated body
 */
class WhileStatement : public IterationStatement {
public:
  virtual ~WhileStatement(){};
  virtual std::string getNodeType() const { return "while"; };
  WhileStatement(const Expression *c, const Statement *s)
      : IterationStatement(c, s) {}
};

class ForStatement : public IterationStatement {
private:
  int num;
  const ExpressionStatement *cond1;
  const ExpressionStatement *cond2;

public:
  virtual ~ForStatement() {
    if (num == 2) {
      delete cond1;
    }
    if (num == 3) {
      delete cond2;
    }
  }
  virtual std::string getNodeType() const { return "For"; };
  ForStatement(const ExpressionStatement *c1, const ExpressionStatement *c2,
               const Statement *s)
      : IterationStatement(new ExpressionList({}), s), cond1(c1), cond2(c2) {
    num = 2;
  }
  ForStatement(const ExpressionStatement *c1, const ExpressionStatement *c2,
               const Expression *c, const Statement *s)
      : IterationStatement(c, s), cond1(c1), cond2(c2) {
    num = 3;
  }
};

/**
 * \brief DoWhileStatement
 *
 * do statement while ( expression )
 */
class DoWhileStatement : public WhileStatement {
public:
  virtual ~DoWhileStatement(){};
  virtual std::string getNodeType() const { return "DoWhile"; };
  DoWhileStatement(const Expression *c, const Statement *s)
      : WhileStatement(c, s) {}
};

/**
 * \brief SelectionStatement
 *
 * Can be If, IfElse and Switch
 */
class SelectionStatement : public ConditionalStatement {
public:
  SelectionStatement(const Expression *c, const Statement *s)
      : ConditionalStatement(c, s) {}
  virtual std::string getNodeType() const { return "SelectionStatement"; };
};

/**
 * \brief IfStatement
 *
 * Executes body (stat1) depending on condition
 */
class IfStatement : public SelectionStatement {
public:
  virtual ~IfStatement(){};
  virtual std::string getNodeType() const { return "If"; };
  IfStatement(const Expression *c, const Statement *s)
      : SelectionStatement(c, s) {}
};

/**
 * \brief IfElseStatement
 *
 * Executes stat1 or stat2 depending on condition
 */
class IfElseStatement : public IfStatement {
private:
  const Statement *stat2;

public:
  IfElseStatement(const Expression *c, const Statement *s1, const Statement *s2)
      : IfStatement(c, s1), stat2(s2) {}
  virtual std::string getNodeType() const { return "IfElse"; };
  virtual void print_xml() const;
};

/*
 * Constraints

The controlling expression of a switch statement shall have integral type. The
expression of each case label shall be an integral constant expression. No two
of the case constant expressions in the same switch statement shall have the
same value after conversion. There may be at most one default label in a switch
statement. (Any enclosed switch statement may have a default label or case
constant expressions with values that duplicate case constant expressions in the
enclosing switch statement.)

Semantics

A switch statement causes control to jump to, into, or past the statement that
is the switch body, depending on the value of a controlling expression, and on
the presence of a default label and the values of any case labels on or in the
switch body. A case or default label is accessible only within the closest
enclosing switch statement.

The integral promotions are performed on the controlling expression. The
constant expression in each case label is converted to the promoted type of the
controlling expression. If a converted value matches that of the promoted
controlling expression, control jumps to the statement following the matched
case label. Otherwise, if there is a default label, control jumps to the labeled
statement. If no converted case constant expression matches and there is no
default label, no part of the switch body is executed.
 */
class SwitchStatement : public SelectionStatement {};


/*! \brief JumpStatement
 * 
 * A jump statement causes an unconditional jump to another place
 */
class JumpStatement : public Statement {
public:
  JumpStatement(){};
  virtual ~JumpStatement(){};
};
/*!
Constraints

The identifier in a goto statement shall name a label located somewhere in the current function.

Semantics

A goto statement causes an unconditional jump to the statement prefixed by the named label in the current function. 
 */
class GotoStatement : public JumpStatement {
private:
  std::string label;
public:
  GotoStatement(const std::string l) : label(l) {};
  virtual ~GotoStatement(){};
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
};

//! \brief CompoundStatement
//! 
//! Any number of declarations (including 0), followed by any number of
//! statements
class CompoundStatement : public Statement {
private:
  const List *declars;
  const List *stats;
public:
  virtual ~CompoundStatement() {
    delete declars;
    delete stats;
  };
  CompoundStatement(const List *_d, const List *_s) : declars(_d), stats(_s){};
  virtual std::string getNodeType() const { return "CompoundStatement"; };
  virtual void print_xml() const;
};

/*! \nrief LabeledStatement
Constraints

A case or default label shall appear only in a switch statement. Further constraints on such labels are discussed under the switch statement.

Semantics

Any statement may be preceded by a prefix that declares an identifier as a label name. Labels in themselves do not alter the flow of control, which continues unimpeded across them. 
 */
class LabeledStatement : public Statement {
private:
  std::string id;
  const Node *stat;
public:
  virtual ~LabeledStatement(){};
  LabeledStatement(std::string _id, const Node *_stat) : id(_id), stat(_stat){};
};

class CaseLabel : public Statement {
private:
  const Expression *expr;
  const Statement *stat;

public:
  virtual ~CaseLabel(){};

  CaseLabel(const Expression *_expr, const Statement *_stat) : expr(_expr), stat(_stat){};
};

class DefaultLabel : public LabeledStatement {};

//! A function has two children (parameter-list, then a statement)
//! It also needs to print out it's id
class Function : public Node {
private:
  const Declarator *declarator;
  const CompoundStatement *stat;

public:
  virtual ~Function(){};

  Function(const Node *_dec,const Node *_s)
      : declarator((const Declarator *)_dec), // Declarator contains the params
        stat((const CompoundStatement *)_s) {}

  // print functions
  virtual std::string getNodeType() const { return "Function"; };
  virtual std::string getHeader() const {
    return "<" + getNodeType() + " id=\"" + declarator->getHeader() + "\">";
  }
  virtual void print_xml() const;
};

#endif
