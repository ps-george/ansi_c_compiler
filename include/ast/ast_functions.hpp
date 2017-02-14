#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"
#include "ast_operators.hpp"

class Function
    : public Expression
{
private:
    const Expression *arg;
protected:
    Function(const Expression *_arg)
        : arg(_arg)
    {}
public:

    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    const Expression *getArg() const
    { return arg; }

    virtual void print_xml() const override
    {
        std::cout<<"<Function id=\""<<getFunction()<<"\">\n";
          this->tab(true);
            arg->print_xml();
          this->tab(false);
        std::cout<<"</Function>\n";
    }
};


#endif
