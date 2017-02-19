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
  virtual ~List() {
    for (auto &it : children)
      delete it;
    children.clear();
  }
  
  virtual std::string getType() const {
    return "List";
  };
  
  virtual std::vector<const Node *> getChildren() const {return children;};
  
  // Print out all children on the same level -> Using list to store lists of things
  virtual void print_xml() const {
      print_children();
  }
  
  virtual void print_children() const {
    for (auto &it : getChildren()) {
      it->print_xml();
    }
  };
  
  // Add a child
  virtual const Node * add(const Node * child) const {
    children.push_back(child);
    return this;
  };
  
};

//! TabbedList is a node of the ast that can have any number of children
//! Name chosen to be list because listes can have other listes
//! or leaves
class TabbedList : public List {
public:
  //! Initialise using brace initializer new TabbedList({arg1, arg2, arg3})
  TabbedList(std::vector<const Node *> _children) : List(_children) {}

  virtual std::string getType() const {
    return "TabbedList";
  };
  
  //! Return the child at a particular index
  //const Node *getChild(int i) const { return children.at(i); }
  
  virtual void print_xml() const {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
    // Print out all children on the same level -> Using list to store lots lists of things
    print_children();
    tab(false);
    std::cout << getFooter() << std::endl;
  }
};

//! The root of the ast
//! It is a list because it can have any number of children
class Program : public TabbedList {
public:
  Program(std::vector<const Node *> _children) : TabbedList(_children) {}
  // Print functions
  virtual std::string getType() const {
    return "Program";
  };
};

//! A function has two children (parameter-list, then a statement)
//! It also needs to print out it's id
class Function : public TabbedList {
private:
  std::string id;
public:
  Function(std::string *_id, std::vector<const Node *> _children) : TabbedList(_children), id(*_id) {}
  // print functions
  virtual std::string getType() const {
    return "Function";
  };
  virtual std::string getHeader() const {
    return "<" + getType() + " id =\"" + id + "\">";
  }
};

#endif
