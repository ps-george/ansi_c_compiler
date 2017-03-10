#ifndef LIST_HPP_
#define LIST_HPP_

#include "node.hpp"
#include "expression.hpp"

#include <iostream>
#include <string>
#include <vector>



class List : public Node {
  //! Contains a vector of pointers to ast nodes
protected:
  mutable std::vector<const Node *> children;
public:
  //! Initialise using brace initializer new List({arg1, arg2, arg3})
  List(std::vector<const Node *> _children) : children(_children) {}
  
  //! Destructor for list
  virtual ~List();
  
  //! Add a child
  virtual const Node * add(const Node * child) const;
  
  //! Return the child at a particular index
  //const Node *getChild(int i) const;
  
  //! Getters
  virtual std::string getNodeType() const;
  virtual std::vector<const Node *> getChildren() const;
  
  //! Printers
  virtual void print_xml(std::ostream &stream) const;
  // virtual void print_c() const;
};

//! TabbedList is a node of the ast that can have any number of children
//! Name chosen to be list because listes can have other listes
//! or leaves
class TabbedList : public List {
public:
  //! Initialise using brace initializer new TabbedList({arg1, arg2, arg3})
  TabbedList(std::vector<const Node *> _children) : List(_children) {}
  
  //! Getters
  virtual std::string getNodeType() const;
  
  //! Printers
  virtual void print_xml(std::ostream &stream) const;
};



//! The root of the ast
//! It is a list because it can have any number of children
class Program : public TabbedList {
public:
  Program(std::vector<const Node *> _children) : TabbedList(_children) {}
  
  //! Getters
  virtual std::string getNodeType() const override;
  // virtual void print_c() const;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
};

//! Scopes have a declaration list
class DeclarationList : public List {
public:
  DeclarationList(std::vector<const Node *> _stems) : List(_stems)  {}
  //! Getters
  virtual std::string getNodeType() const override;
  //! Printers
  virtual void print_xml(std::ostream &stream) const override;
};

//! Functions have a parameter list.
class ParameterList : public DeclarationList {
public:
  ParameterList(std::vector<const Node *> _stems) : DeclarationList(_stems) {}
  //! Getters
  virtual std::string getNodeType() const override;
  //! Printers
  virtual void print_xml(std::ostream &stream) const override;
};

//! Points to any number of expressions separated by commas
class ExpressionList : public List, public Expression {
  //! Contains a vector of pointers to ast nodes
public:
  virtual ~ExpressionList(){};
  ExpressionList(std::vector<const Node *> _children) : List(_children) {}
  //! Getters
  virtual std::string getNodeType() const override;
  virtual std::vector<const Node *> getChildren() const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
  virtual void print_xml(std::ostream &stream) const override;
};

#endif
