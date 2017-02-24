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
  
  virtual const Declaration * add(const DeclarationList * d) const{
    dlist = d;
    return this;
  }
};

#endif
