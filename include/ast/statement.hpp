#ifndef STATEMENT_HPP_
#define STATEMENT_HPP_

#include "declaration.hpp"
#include "expression.hpp"
#include "list.hpp"
#include "node.hpp"

//! An expression evaluated as void for its side-effects
class ExpressionStatement : public Statement {
private:
  const Expression *expr;
public:
  ExpressionStatement(const Expression *e) : expr(e){};
  ~ExpressionStatement(){};
  virtual std::string getNodeType() const override { return "ExpressionStatement"; };
  virtual std::vector<const Node *> getChildren() const override { return {expr}; }
  virtual Context print_asm(Context ctxt) const override;
  virtual void print_xml(std::ostream& stream) const override;
};

/*!
 * \brief ConditionalStatement (can be Selection or Iteration)
 *
 * Has an Expression as the condition, Statement as result
 */
class ConditionalStatement : public Statement {
protected:
  const Statement *stat1;

public:
  virtual ~ConditionalStatement() {
    delete stat1;
  };
  //! Constructor with Expression and Statement
  ConditionalStatement(const Statement *s)
      : stat1(s) {}
  virtual std::string getNodeType() const { return "ConditionalStatement"; };
  virtual void print_xml(std::ostream &stream) const;
  // virtual void print_c() const;
  virtual std::vector<const Expression *>getConditions() const = 0;
  virtual const Statement *getBody() const { return stat1; };
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
  virtual std::string getNodeType() const override;
  virtual std::vector<const Node *> getChildren() const override;
  virtual void print_xml(std::ostream &stream) const override;
  virtual Context print_asm(Context ctxt) const override;
};

#endif
