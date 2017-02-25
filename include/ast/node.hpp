#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <string>
#include <vector>

//! Abstract base class for ast node
class Node {
private:
  static int tabcount;
  static int changed;
public:
  virtual ~Node(){};
  
  //! Getters
  virtual std::string getNodeType() const = 0;  //! Return the type of the node
  virtual std::string getHeader() const;        //! Return the xml header for the node
  virtual std::string getFooter() const;        //! Return the xml footer for the node
  virtual std::string getId() const;            //! Return the id of a variable, ideally should be pure virtual
  
  //! Printers
  virtual void print_xml() const;    //! Print xml implicit recursive function
  virtual void print_c() const;      //! Print cpp implicit recursive function
  // virtual void print_mips() const;   //! Print ast 
  
  //! Static functions for keeping xml indentation nice
  static void tab(bool open);
  static void tab_incr() { tabcount++; }
  static void tab_decr() { tabcount--; }
  static void tab() { if (tabcount) std::cout << std::string(tabcount, '\t'); } //! Return   
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