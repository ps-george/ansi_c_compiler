#ifndef ast_list_hpp
#define ast_list_hpp

#include "ast_leaf.hpp"
#include "ast_branch.hpp"

#include <iostream>
#include <string>
#include <vector>

//! A list is like a branch but everything is on the same level and we don't print out the type name at all
//! it is just a container
class List : public Branch {
public:
  List(std::vector<const Leaf *> _stems) : Branch(_stems) {}
  
  // Print out all stems on the same level -> Using list to store lists of things
  virtual void print_xml() const override {
    if (stems.size()>0)
      print_stems();
  }
  
  virtual std::string getType() const override {
    return "List";
  };
};

//! Functions have a parameter list.
class ParameterList : public List {
public:
  ParameterList(std::vector<const Leaf *> _stems) : List(_stems) {}
  
  // Print out all stems on the same level -> Using list to store lists of things
  virtual void print_xml() const override {
    if (stems.size()>0)
      print_stems();
  }
  
  virtual std::string getType() const override {
    return "ParameterList";
  };
};

//! Scopes have a declaration list
class DeclarationList : public List {
public:
  DeclarationList(std::vector<const Leaf *> _stems) : List(_stems) {}
  
  // Print out all stems on the same level -> Using list to store lists of things
  virtual void print_xml() const override {
    if (stems.size()>0)
      print_stems();
  }
  virtual std::string getType() const override {
    return "DeclarationList";
  };
};

#endif
