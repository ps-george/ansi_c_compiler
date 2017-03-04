#ifndef SELECTION_STATEMENT_HPP
#define SELECTION_STATEMENT_HPP

#include "statement.hpp"

/**
 * \brief SelectionStatement
 *
 * Can be If, IfElse and Switch
 */
class SelectionStatement : public ConditionalStatement {
private:
  const Expression *cond;
public:
  SelectionStatement(const Expression *c, const Statement *s)
      : ConditionalStatement(s), cond(c) {}
  virtual std::string getNodeType() const { return "SelectionStatement"; };
  virtual const Expression *getCondition() const;
  virtual std::vector<const Expression *>getConditions() const;
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
  virtual void print_xml(std::ostream &stream) const;
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
  virtual void print_xml(std::ostream &stream) const;
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

#endif
