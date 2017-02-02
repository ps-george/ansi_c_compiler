#ifndef ast_primitives_hpp
#define ast_primitives_hpp

// To satisfy my linter...
#include "ast/ast_expression.hpp"

#include <string>
#include <iostream>

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print() const override
    {
        std::cout<<value;
    }
    
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      return this->getValue();
    }
    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    { 
    return new Number(0); }    
};

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print() const override
    {
        std::cout<<id;
    }
    
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      return bindings.find(this->getId())->second;
    }
    
    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    { 
    if (variable == this->getId()){
      return new Number(1);
    }
      return new Number(0); 
    }    

};



#endif
