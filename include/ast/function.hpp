#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "statement.hpp"

//! A function has two children (parameter-list, then a statement)
//! It also needs to print out it's id
class Function : public Node {
private:
  const Declarator *declarator;
  const CompoundStatement *stat;

public:
  virtual ~Function(){};

  Function(const Node *_dec, const Node *_s)
      : declarator((const Declarator *)_dec), // Declarator contains the params
        stat((const CompoundStatement *)_s) {}

  // print functions
  virtual std::string getNodeType() const { return "Function"; };
  virtual std::string getHeader() const {
    return "<" + getNodeType() + " id=\"" + declarator->getId() + "\">";
  }
  virtual void print_xml() const;
};

#endif
