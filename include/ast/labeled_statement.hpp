#ifndef LABELED_STATEMENT_HPP_
#define LABELED_STATEMENT_HPP_

#include "statement.hpp"
/*! \brief LabeledStatement
Constraints

A case or default label shall appear only in a switch statement. Further
constraints on such labels are discussed under the switch statement.

Semantics

Any statement may be preceded by a prefix that declares an identifier as a label
name. Labels in themselves do not alter the flow of control, which continues
unimpeded across them.
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

  CaseLabel(const Expression *_expr, const Statement *_stat)
      : expr(_expr), stat(_stat){};
};

class DefaultLabel : public LabeledStatement {};

#endif
