#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "statement.hpp"
#include "type.hpp"

//! A function has two children (parameter-list, then a statement)
//! It also needs to print out it's id
class Function : public Node {
private:
  const Type *type;
  const Declarator *declarator;
  const CompoundStatement *stat;

public:
  virtual ~Function(){};

  Function(const Node *_type, const Node *_dec, const Node *_s);

  //! Getters
  virtual std::string getType() const;
  virtual std::string getNodeType() const { return "Function"; };
  virtual std::string getHeader() const;
  
  //! print functions
  virtual void print_xml() const;
  virtual void print_c() const;
};

#endif
