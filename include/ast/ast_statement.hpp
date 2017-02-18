#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <iostream>
#include <map>
#include <string>

#include "ast_leaf.hpp"
#include "ast_branch.hpp"

//! Abstract base class for the different types of statement
class Statement : public Leaf {

public:
  virtual ~Statement() {}
  virtual std::string getType() const override {
    return "Statement";
  };
  
  virtual void print_xml() const override = 0;
  virtual std::vector<const Leaf *> getAllStems() const override {
    std::vector<const Leaf *> v {this};
    return v;
  }
  
  virtual const Leaf * add(const Leaf * l) const override {
    return this;
  }
};

//! Clas
class CompoundStatement : public Statement {
public:
  
};

//! Abstract base class for If, IfElse and Switch statements
class ConditionalStatement : public Statement {
private:
  const Leaf* condition;
public:
  virtual ~ConditionalStatement() {}
  ConditionalStatement(const Leaf* _cond) : condition(_cond) {};
  virtual const Leaf* getCondition() const { return condition; }
  
  virtual std::string getType() const override {
    return "Scope";
  };
  
  virtual void print_xml() const override = 0;
};

//! Class for if statement
class IfStatement : public ConditionalStatement {
private:
  const Leaf* ifstat;
public:
  IfStatement(const Leaf* _cond, const Leaf* _ifstat) : ConditionalStatement(_cond), ifstat(_ifstat) {};
  
  virtual void print_xml() const override {
    this->tab();
    std::cout << getHeader();
    std::cout << "\n";
    this->tab_incr();
    ifstat->print_xml();
    this->tab(false);
    std::cout << "</" << getType() << ">\n";
  }
};

//! Class for if else statement
class IfElseStatement : public IfStatement {
private:
  const Leaf* elsestat;
public:
  IfElseStatement(const Leaf* _cond, const Leaf* _ifstat, const Leaf* _elsestat) : IfStatement(_cond,_ifstat), elsestat(_elsestat) {};
  
  virtual void print_xml() const override {
    IfStatement::print_xml();
    this->tab();
    std::cout << getHeader();
    std::cout << "\n";
    this->tab_incr();
    elsestat->print_xml();
    this->tab(false);
    std::cout << "</" << getType() << ">\n";
  }
};

#endif
