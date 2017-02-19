#ifndef AST_STATEMENT_HPP
#define AST_STATEMENT_HPP

#include "ast_node.hpp"
#include "ast_list.hpp"
#include "ast_expression.hpp"

class Statement : public Node {};

class IterationStatement : public Statement {};
class WhileStatement : public IterationStatement {};
class ForStatement : public IterationStatement {};
class DoWhileStatement : public IterationStatement {};

class SelectionStatement : public Statement {};
class IfStatement : public SelectionStatement {};
class IfElseStatement : public SelectionStatement {};
class SwitchStatement : public SelectionStatement {};

class JumpStatement : public Statement {};
class GotoStatement : public JumpStatement {};
class ContinueStatement : public JumpStatement {};
class BreakStatement : public JumpStatement {};
class ReturnStatement : public JumpStatement {};

//! An expression evaluated as void for its side-effects
class ExpressionStatement : public Statement {};

//! Any number of declarations (including 0), followed by any number of statements
class CompoundStatement : public Statement {
private:
  const List * declarationList;
  const List * statementList;
};

class LabeledStatement : public Statement {
private:
  std::string id;
  const Statement * stat;
};

class CaseLabel : public Statement {
private:
  const ConstantExpression * expr;
  const Statement * stat;
};

class DefaultLabel : public CaseLabel {
  
};

#endif
