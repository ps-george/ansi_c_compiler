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
    
    virtual void print_xml() const override
    {
        std::cout<<"<Number value=\""<< value << "\"/>\n";
    }
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
    
    virtual void print_xml() const override
    {
        std::cout<<"<Variable id=\""<< id << "\"/>\n";
    }
};



#endif
