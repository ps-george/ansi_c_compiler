#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "codegen_helpers.hpp"

//! Abstract base class for ast node
class Node {
private:
  static int tabcount;
  static int changed;
  static std::vector<std::string> strings;
protected:
  mutable int sourceline;
  mutable int sourcecol;
  static bool parser;
  // metadata;
  mutable std::vector<std::string> childDefs; //! Child defs and
  //mutable std::map<std::string, int> childUses; //! Child uses easier to implement (??) (are they necessary?)
  // std::vector<std::string> parentDefs; -> need pointer to parent on each node, effort.
  
  // A list of:
  // variables used by children
  // variables defined by parents
  // variables defined by children
  // def-use analysis
public:
  virtual ~Node(){};
  Node();
  //! Getters
  virtual std::string getNodeType() const;  //! Return the type of the node
  virtual std::string getDeets() const;
  virtual std::string getHeader() const;        //! Return the xml header for the node
  virtual std::string getFooter() const;        //! Return the xml footer for the node
  virtual std::vector<const Node *> getChildren() const { return {};}; //! If not overridden, return empty.
  virtual std::string getId() const;            //! Return the id of a variable, ideally should be pure virtual
  virtual std::vector<std::string> getChildDefs() const; //! Child defs is the most useful, especially for functions
  virtual void addString(std::string) const;
  virtual std::vector<std::string> getStrings() const;
  //virtual std::map<std::string> childUses() const;
  // virtual void childUses() const;
  
  //! Recursive setter:
  virtual void setChildDefs() const;
  //! Printers
  virtual void print_xml(std::ostream &stream) const;    //! Print xml implicit recursive function
  // virtual void print_c() const;      //! Print cpp implicit recursive function
  virtual Context print_asm(Context ctxt, int d = 2) const; //! Print out mips assembly
  // virtual void print_mips() const;   //! Print ast 
  
  //! Static functions for keeping xml indentation nice
  static void tab(std::ostream &stream, bool open);
  static void tab_incr() { tabcount++; }
  static void tab_decr() { tabcount--; }
  static void tab(std::ostream &stream) { if (tabcount) stream << std::string(tabcount, '\t'); } //! Return   
  //! Return a vector containing all of the children of the node
  //virtual std::vector<const Node *> getChildren() const = 0;
  
  //! For fixed point optimisation algos, probably won't use for coursework submission
  //static void change() { changed++; }
  //int getChanged() { return changed; }
  //virtual const Node * constant_fold() const = 0;
  //virtual const Node * constant_propagation() const = 0;
  //virtual const Node * dead_branch_removal() const = 0;
};

#endif
