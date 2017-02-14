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
  //! Initialise using brace initializer new Branch({arg1, arg2, arg3})
  Branch(std::vector<const Leaf *> _stems) : stems(_stems) {}

public:
  //! Destructor for branch
  virtual ~Branch() {
    for (auto &it : stems)
      delete it;
    stems.clear();
  }

  virtual const char *getBranch() const = 0;

  //! Return the stem at a particular index
  const Leaf *getStem(int i) const { return stems.at(i); }

  virtual void print_xml() const override {
    std::cout << "<Branch id=\"" << getBranch() << "\">\n";
    for (auto &it : stems) {
      this->tab(true);
        it->print_xml();
      this->tab(false);
    }
    std::cout << "</Branch>\n";
  }
};

//! The root of the ast
class Root : public Branch {
public:
};

//! A function has ...
class Function : public Branch {};

#endif
