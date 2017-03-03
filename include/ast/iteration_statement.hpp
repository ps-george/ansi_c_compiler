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
  // virtual std::vector<const Node *> getChildren() const;
  // virtual std::vector<const Expression*> getConditions() const = 0;
  // virtual void print_c() const;
  IterationStatement(const Statement *s)
      : ConditionalStatement(s) {}
  virtual std::vector<const Node *> getChildren() const = 0;
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
  virtual std::string getNodeType() const override;
  virtual std::vector<const Expression*> getConditions() const override {
    return {cond};
  };
  WhileStatement(const Expression *c, const Statement *s)
      : IterationStatement(s), cond(c) {}
  virtual std::vector<const Node *> getChildren() const override;
};


/**
 * \brief DoWhileStatement
 *
 * do statement while ( expression )
 */
class DoWhileStatement : public WhileStatement {
public:
  virtual ~DoWhileStatement(){};
  virtual std::string getNodeType() const override;
  DoWhileStatement(const Statement *s, const Expression *c)
      : WhileStatement(c, s) {}
};


class ForStatement : public IterationStatement {
protected:
  const ExpressionStatement *cond1;
public:
  virtual std::string getNodeType() const override;
  ForStatement(const ExpressionStatement *c1, const Statement *s1)
      : IterationStatement(s1), cond1(c1)  {};
  virtual std::vector<const Expression*> getConditions() const override {
    return {(const Expression*)cond1};
  };
  virtual std::vector<const Node *> getChildren() const override;
};

class EEForStatement : public ForStatement {
protected:
  const ExpressionStatement *cond2;
public:
  EEForStatement(const ExpressionStatement *c1, const ExpressionStatement *c2,
                 const Statement *s1)
      : ForStatement(c1,s1), cond2(c2) {};
  
  virtual std::vector<const Expression*> getConditions() const override {
    return {(const Expression*)cond1,(const Expression*)cond2};
  };
  virtual std::vector<const Node *> getChildren() const override;
};

class EEEForStatement : public EEForStatement {
private:
  const Expression *cond3;
public:
  EEEForStatement(const ExpressionStatement *c1, const ExpressionStatement *c2,
                  const Expression *c3, const Statement *s1)
      : EEForStatement(c1,c2,s1), cond3(c3)  {}
  ;
  virtual std::vector<const Expression*> getConditions() const override {
    return {(const Expression*)cond1,(const Expression*)cond2, cond3};
  };
  virtual std::vector<const Node *> getChildren() const override;
};

class DEForStatement : public ForStatement {
protected:
  const Declaration *dec;
public:
  DEForStatement(const Declaration *d, const ExpressionStatement *c1,
                 const Statement *s1)
      :  ForStatement(c1,s1), dec(d)  {};
  ;
  virtual std::vector<const Expression*> getConditions() const override {
    return {(const Expression*)cond1};
  };
  virtual std::vector<const Node *> getChildren() const override;
  //virtual void print_xml(std::ostream& stream) const override;
};

class DEEForStatement : public DEForStatement {
private:
  const Expression *cond2;
public:
  DEEForStatement(const Declaration *d, const ExpressionStatement *c1,
                  const Expression *c2, const Statement *s1)
      : DEForStatement(d, c1, s1), cond2(c2)  {};
  ;
  virtual std::vector<const Expression*> getConditions() const override {
    return {(const Expression*)cond1,cond2};
  };
  virtual std::vector<const Node *> getChildren() const override;
};

#endif
