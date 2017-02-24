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
};

//! Functions have a parameter list.
class ParameterList : public DeclarationList {
public:
  ParameterList(std::vector<const Node *> _stems) : DeclarationList(_stems) {}
  virtual std::string getNodeType() const override { return "ParameterList"; };
};

//! A declarator is what we are declaring; it is essentially just an ID when it follows a specifier.
class Declarator : public Primitive {
std::string id;
public:
  Declarator(std::string * _id) : id(*_id) {};
  virtual std::string getNodeType() const override { return "Declarator"; };
};

//! Init declarator

class InitDeclarator : public Declarator {
const Expression * e;
public:
  InitDeclarator(std::string * _id, const Expression * _e) : Declarator(_id), e(_e) {};
  virtual std::string getNodeType() const override { return "InitDeclarator"; };
};

//! \brief A declaration of a variable
//! 
//! A declaration has a type and a list of declared things
class Declaration : public Node {
private:
  const Type * type;
  mutable const DeclarationList * dlist;
public:
  Declaration(const Type * t, const DeclarationList * d) : type(t), dlist(d){};
  Declaration(const Type * t) : type(t), dlist(nullptr) {};
  virtual std::string getNodeType() const override { return "Declaration"; };
  virtual const Declaration * add(const DeclarationList * d) const{
    dlist = d;
    return this;
  }
};

#endif
