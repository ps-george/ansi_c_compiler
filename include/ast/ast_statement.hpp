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
  const List * declars;
  const List * stats;
public:
  CompoundStatement(const List * _d, const List * _s) : declars(_d), stats(_s) {};
  
  virtual std::string getType() const {return "Scope";};
  
  inline virtual void print_xml() const {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
      declars->print_xml();
      stats->print_xml();
    tab(false);
    std::cout << getFooter() << std::endl;
  }
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

//! A function has two children (parameter-list, then a statement)
//! It also needs to print out it's id
class Function : public Node {
private:
  std::string id;
  const ParameterList * params;
  const CompoundStatement * stat;
public:
//  Function(std::string *_id, std::vector<const Node *> _children) : TabbedList(_children), id(*_id) {}
  // print functions
  virtual std::string getType() const {
    return "Function";
  };
  virtual std::string getHeader() const {
    return "<" + getType() + " id =\"" + id + "\">";
  }
};

#endif
