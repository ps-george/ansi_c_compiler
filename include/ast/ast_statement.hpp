#ifndef AST_STATEMENT_HPP
#define AST_STATEMENT_HPP

#include "ast_node.hpp"
#include "ast_list.hpp"
#include "ast_expression.hpp"

class Statement : public Node {
public:
  virtual ~Statement(){};
  virtual std::string getType() const {return "Statement";};
};

class ConditionalStatement : public Statement {
protected:
  const Node * cond1;
  const Node * stat1;
public:
  virtual ~ConditionalStatement(){
    delete cond1;
    delete stat1;
  };
  ConditionalStatement(const Node * c, const Node * s) : cond1(c),stat1(s){}
  virtual std::string getType() const {return "ConditionalStatement";};
  
  inline virtual void print_xml() const {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
      //cond1->print_xml();
      stat1->print_xml();
    tab(false);
    std::cout << getFooter() << std::endl;
  }
};

class IterationStatement : public ConditionalStatement {
public:
  virtual ~IterationStatement(){};
  
  virtual std::string getType() const {return "IterationStatement";}; 
  IterationStatement(const Node * c, const Node * s) : ConditionalStatement(c,s){}
};

class WhileStatement : public IterationStatement {
public:
  virtual ~WhileStatement(){};
  WhileStatement(const Node * c, const Node * s) : IterationStatement(c,s){}
};

class ForStatement : public IterationStatement {
private:
  int num;
  const Node * cond2;
  const Node * cond3;
public:
  virtual ~ForStatement(){
    if (num > 2){ delete cond2; }
    if (num==3) { delete cond3; }
  }
  ForStatement(const Node * c1, const Node * s) : IterationStatement(c1,s) {
    cond2 = nullptr;
    cond3 = nullptr;
    num = 1;
  }
  ForStatement(const Node * c1, const Node * c2, const Node * s) : IterationStatement(c1,s), cond2(c2) {
    cond3 = nullptr;
    num = 2;
  }
  ForStatement(const Node * c1, const Node * c2, const Node * c3, const Node * s) : IterationStatement(c1,s), cond2(c2), cond3(c3) { num = 3; }
};
class DoWhileStatement : public IterationStatement {};

class SelectionStatement : public ConditionalStatement {
public:
  SelectionStatement(const Node * c, const Node * s) : ConditionalStatement(c,s){}
  
};

class IfStatement : public SelectionStatement {
public:
  virtual ~IfStatement(){};
  IfStatement(const Node * c, const Node * s) : SelectionStatement(c,s) {}
};
class IfElseStatement : public IfStatement {
private:
  const Node * stat2;
public:
  IfElseStatement(const Node * c, const Node * s1, const Node * s2) : IfStatement(c,s1),stat2(s2){}
  
  inline virtual void print_xml() const {
    IfStatement::print_xml();
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
      //cond1->print_xml();
      stat2->print_xml();
    tab(false);
    std::cout << getFooter() << std::endl;
  }
};
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
  virtual ~CompoundStatement(){
    delete declars;
    delete stats;
  };
  CompoundStatement(const List * _d, const List * _s) : declars(_d), stats(_s) {};
  
  virtual std::string getType() const {return "CompoundStatement";};
  
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
public:
  virtual ~LabeledStatement(){};
  
  LabeledStatement(std::string _id, const Statement * _stat) : id(_id), stat(_stat) {};
};

class CaseLabel : public Statement {
private:
  const ConstantExpression * expr;
  const Statement * stat;
public:
  virtual ~CaseLabel(){};
  
  CaseLabel(const ConstantExpression * _expr, const Statement * _stat) : expr(_expr),stat(_stat) {};
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
  virtual ~Function(){};
  
  Function(std::string *_id, const Node * _p, const Node * _s) 
    : id(*_id), params((const ParameterList *)_p), stat((const CompoundStatement *)_s)  {}
  // print functions
  virtual std::string getType() const {
    return "Function";
  };
  virtual std::string getHeader() const {
    return "<" + getType() + " id=\"" + id + "\">";
  }
  inline virtual void print_xml() const {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
      params->print_xml();
      stat->print_xml();
    tab(false);
    std::cout << getFooter() << std::endl;
  }
};

#endif
