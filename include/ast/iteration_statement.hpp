#ifndef ITERATION_STATEMENT_HPP_
#define ITERATION_STATEMENT_HPP_

#include "statement.hpp"

/*!
 * \brief IterationStatement
 *
 * Has an Expression as the condition, Statement as iterated body
 */
class IterationStatement : public ConditionalStatement {
public:
  virtual ~IterationStatement(){};
  virtual std::string getNodeType() const;
  virtual std::vector<const Expression*> getConditions() const = 0;
  virtual void print_c() const;
  IterationStatement(const Statement *s)
      : ConditionalStatement(s) {}
};

/*!
 * \brief WhileStatement
 *
 * Has an Expression as the condition, Statement as iterated body
 */
class WhileStatement : public IterationStatement {
private:
  const Expression *cond;
public:
  virtual ~WhileStatement(){};
  virtual std::string getNodeType() const override { return "while"; };
  virtual std::vector<const Expression*> getConditions() const override {
    return {cond};
  };
  WhileStatement(const Expression *c, const Statement *s)
      : IterationStatement(s), cond(c) {}
};

class ForStatement : public IterationStatement {
private:
  const ExpressionStatement *cond1;

public:
  virtual std::string getNodeType() const override { return "For"; };
  ForStatement(const ExpressionStatement *c1, const Statement *s1)
      : IterationStatement(s1), cond1(c1)  {};
  virtual std::vector<const Expression*> getConditions() const override {
    return {(const Expression*)cond1};
  };
};

class EEForStatement : public ForStatement {
private:
  const ExpressionStatement *cond2;

public:
  EEForStatement(const ExpressionStatement *c1, const ExpressionStatement *c2,
                 const Statement *s1)
      : ForStatement(c1, s1), cond2(c2) {};
};

class EEEForStatement : public EEForStatement {
private:
  const Expression *cond3;

public:
  EEEForStatement(const ExpressionStatement *c1, const ExpressionStatement *c2,
                  const Expression *c3, const Statement *s1)
      : EEForStatement(c1, c2, s1), cond3(c3)  {};
};

class DEForStatement : public ForStatement {
private:
  const Declaration *dec;

public:
  DEForStatement(const Declaration *d, const ExpressionStatement *c1,
                 const Statement *s1)
      :  ForStatement(c1, s1), dec(d)  {};
};

class DEEForStatement : public DEForStatement {
private:
  const Expression *cond2;
public:
  DEEForStatement(const Declaration *d, const ExpressionStatement *c1,
                  const Expression *c2, const Statement *s1)
      : DEForStatement(d, c1, s1), cond2(c2)  {};
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
  DoWhileStatement(const Statement *s, const Expression *c)
      : WhileStatement(c, s) {}
};

#endif
