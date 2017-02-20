#ifndef ast_list_hpp
#define ast_list_hpp

#include "ast_node.hpp"

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
  
  virtual std::string getType() const { return "List"; };
  
  virtual std::vector<const Node *> getChildren() const { return children; };
  
  // Print out all children on the same level -> Using list to store lists of things
  virtual void print_xml() const { print_children(); }
  
  virtual void print_children() const;
  
  // Add a child
  virtual const Node * add(const Node * child) const;
  
};

//! TabbedList is a node of the ast that can have any number of children
//! Name chosen to be list because listes can have other listes
//! or leaves
class TabbedList : public List {
public:
  //! Initialise using brace initializer new TabbedList({arg1, arg2, arg3})
  TabbedList(std::vector<const Node *> _children) : List(_children) {}

  virtual std::string getType() const {
    return "Scope";
  };
  
  //! Return the child at a particular index
  //const Node *getChild(int i) const { return children.at(i); }
  
  virtual void print_xml() const;
};

//! The root of the ast
//! It is a list because it can have any number of children
class Program : public TabbedList {
public:
  Program(std::vector<const Node *> _children) : TabbedList(_children) {}
  // Print functions
  virtual std::string getType() const { return "Program"; };
};


//! Scopes have a declaration list
class DeclarationList : public List {
public:
  DeclarationList(std::vector<const Node *> _stems) : List(_stems) {}
  virtual std::string getType() const override { return "DeclarationList"; };
};

//! Functions have a parameter list.
class ParameterList : public DeclarationList {
public:
  ParameterList(std::vector<const Node *> _stems) : DeclarationList(_stems) {}
  
  virtual std::string getType() const override { return "ParameterList"; };
};




#endif
