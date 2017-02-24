#ifndef AST_DECLARATION_HPP_
#define AST_DECLARATION_HPP_

#include "ast_list.hpp"
#include "ast_node.hpp"
#include "ast_primitive.hpp"

//! Scopes have a declaration list
class DeclarationList : public List {
public:
  DeclarationList(std::vector<const Node *> _stems) : List(_stems)  {}
  virtual std::string getNodeType() const override { return "DeclarationList"; };
  virtual void print_xml() const override;
};

//! Functions have a parameter list.
class ParameterList : public DeclarationList {
public:
  ParameterList(std::vector<const Node *> _stems) : DeclarationList(_stems) {}
  virtual std::string getNodeType() const override { return "ParameterList"; };
  virtual void print_xml() const override;
};

//! A declarator is what we are declaring; it is essentially just an ID when it follows a specifier.
class Declarator : public Node {
const Node * child;
public:
  Declarator(const Node * _child) : child(_child) {};
  virtual std::string getNodeType() const override { return "Declarator"; };
  virtual std::string getId() const override { return child->getId(); };
  virtual void print_xml() const override;
};

//! Init declarator
class InitDeclarator : public Declarator {
const Expression * e;
public:
  InitDeclarator(const Node * _child, const Expression * _e) : Declarator(_child), e(_e) {};
  virtual std::string getNodeType() const override { return "InitDeclarator"; };
};

//! Array declarator
class ArrayDeclarator : public Declarator {
const Expression * e;
public:
  ArrayDeclarator(const Node * _child, const Expression * _e) : Declarator(_child), e(_e) {};
  virtual std::string getNodeType() const override { return "ArrayDeclarator"; };
};

//! Function declarator
class FunctionDeclarator : public Declarator {
const List * p; //! Parameter list/indentifier list for old-style functions
public:
  FunctionDeclarator(const Node * _child, const List * _p) : Declarator(_child), p(_p) {};
  virtual std::string getNodeType() const override { return "FunctionDeclarator"; };
  virtual void print_xml() const override;
};

//! \brief A declaration of a variable
//! 
//! A declaration has a type and a list of declared things
class Declaration : public Node {
private:
  const Type * type;
  const List * dlist;
public:
  Declaration(const Type * t, const List * d) : type(t), dlist(d){};
  virtual std::string getNodeType() const override { return "Declaration"; };
  virtual void print_xml() const override;
};

#endif
