#ifndef ast_branch_hpp
#define ast_branch_hpp

#include "ast_leaf.hpp"

#include <iostream>
#include <string>
#include <vector>

//! Branch is a node of the ast that can have any number of children
//! Name chosen to be branch because branches can have other branches on them or
//! leafs
class Branch : public Leaf {
private:
  //! Contains a vector of pointers to leaf nodes
  //! Called stems because stems represent anythings stemming off from a branch
protected:
  mutable std::vector<const Leaf *> stems;

public:
  //! Initialise using brace initializer new Branch({arg1, arg2, arg3})
  Branch(std::vector<const Leaf *> _stems) : stems(_stems) {}
  
  //! Destructor for branch
  virtual ~Branch() {
    for (auto &it : stems)
      delete it;
    stems.clear();
  }

  virtual std::string getType() const override {
    return "Branch";
  };
  
  //! Return the stem at a particular index
  const Leaf *getStem(int i) const { return stems.at(i); }
  virtual std::vector<const Leaf *> getAllStems() const override { return stems; }
  
  // Add a stem
  virtual const Leaf * add(const Leaf * l) const override {
    stems.push_back(l);
    return this;
  };
  
  virtual void print_xml() const override {
    std::cout << "<" << getType() << ">\n";
    this->tab_incr();
    // Print out all stems on the same level -> Using branch to store lots lists of things
    for (auto &it : stems) {
        it->print_xml();
    }
    
    this->tab(false);
    std::cout << "</" << getType() << ">\n";
  }
};

//! A list is like a branch but everything is on the same level and we don't print out the type name at all
//! it is just a container
class List : public Branch {
public:
  List(std::vector<const Leaf *> _stems) : Branch(_stems) {}
  
  virtual std::string getType() const override {
    return "List";
  };
  
  virtual void print_xml() const override {
    //std::cout << "<" << getType() << ">\n";
    //this->tab_incr();
    // Print out all stems on the same level -> Using list to store lists of things
    for (auto &it : stems) {
        this->tab();
        it->print_xml();
    }
    //this->tab();
    //std::cout << "</" << getType() << ">\n";
  }
};

//! The root of the ast
//! It is a branch because it can have any number of children
class Program : public Branch {
public:
  Program(std::vector<const Leaf *> _stems) : Branch(_stems) {}
  
  virtual std::string getType() const override {
    return "Program";
  };
};

//! A function has a large number of children (declaration-lists, then a statement)
//! It also needs to print out it's id
class Function : public Branch {
private:
  std::string id;
public:
  Function(std::string *_id, std::vector<const Leaf *> _stems) : Branch(_stems), id(*_id) {}
  
  virtual std::string getType() const override {
    return "Function";
  };
  
  virtual void print_xml() const override {
    this->tab();
    std::cout << "<" << getType() << " id =\"" << id << "\">\n";
    
    this->tab_incr();
    
    if (stems.size()>0){
        for (auto &it : stems) {
          it->print_xml();
        }
    }
    
    this->tab(false);
    std::cout << "</" << getType() << ">\n";
  }
};

#endif
