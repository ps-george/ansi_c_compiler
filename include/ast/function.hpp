#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "statement.hpp"
#include "type.hpp"

//! A function has two children (parameter-list, then a statement)
//! It also needs to print out it's id
class Function : public Node {
private:
  const Type * type; //! Type can get from declaration->getType()
  std::string id; //! Can get from declarator->getId()
  //const List * params; //! Can get from declarator->getParams()
  const FunctionDeclarator * declarator; // This contains id and a pointer to the declarator
  const CompoundStatement *stat;

public:
  virtual ~Function(){};

  Function(const Node *_type, const Node *_dec, const Node *_s);

  //! Getters
  virtual std::string getType() const;
  virtual std::string getNodeType() const { return "Function"; };
  virtual std::string getHeader() const;
  virtual std::string getDeets() const override;
  virtual std::vector<std::string> getParams() const;
  virtual std::string getParamString() const;
  virtual std::vector<const Node *> getChildren() const;
  
  //! Recursive setter:
  virtual void setChildDefs() const override;
  //! print functions
  virtual void print_xml(std::ostream &stream) const;
  // virtual void print_c() const;
  virtual Context print_asm(Context ctxt, int d = 2) const; //! Print out mips assembly
};

#endif
