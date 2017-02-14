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
  //! Called stems because steams represent anythings stemming off from a branch
  std::vector<const Leaf *> stems;

protected:
  

public:
  //! Initialise using brace initializer new Branch({arg1, arg2, arg3})
  Branch(std::vector<const Leaf *> _stems) : stems(_stems) {}
  
  Branch(std::vector<const Leaf *> _stems, const Leaf * s) : stems(_stems) {
    stems.push_back(s);
  }
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
  
  virtual void print_xml() const override {
    std::cout << "<" << getType() << ">\n";
    for (auto &it : stems) {
      this->tab(true);
        it->print_xml();
      this->tab(false);
    }
    std::cout << "</" << getType() << ">\n";
  }
};

//! The root of the ast
class Program : public Branch {
public:
  Program(std::vector<const Leaf *> _stems) : Branch(_stems) {}
  
  Program(std::vector<const Leaf *> _stems, const Leaf * s) : Branch(_stems,s) {
  }
};

//! A function has ...
class Function : public Branch {};

#endif
