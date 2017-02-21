#ifndef AST_NODE_HPP_
#define AST_NODE_HPP_

#include <iostream>
#include <string>
#include <vector>

/* Constructs for parser deliverable:
IfStatement
WhileStatement
ForStatement
Function


 */

//! Abstract base class for ast node
class Node {
private:
  static int tabcount;
  static int changed;
public:
  virtual ~Node(){};
  
  //! Return the type of the node
  
  virtual std::string getNodeType() const = 0;
  
  //! Return the xml header for the node
  virtual std::string getHeader() const { return "<" + getNodeType() + ">"; };
  
  //! Return the xml footer for the node
  virtual std::string getFooter() const { return "</" + getNodeType() + ">"; };
  
  //! Return a vector containing all of the children of the node
  //virtual std::vector<const Node *> getChildren() const = 0;
  /*
  //! Print out the xml for all of the node's children
  virtual void print_children_xml() const {
    for (auto &it : getChildren()) {
      it->print_xml();
    }
  };
  */
  //! Print xml implicit recursive function
  virtual void print_xml() const;
  
  //! Print cpp implicit recursive function
  virtual void print_cpp() const;
  
  /*
  //virtual const Node * constant_fold() const = 0;
  //virtual const Node * constant_propagation() const = 0;
  //virtual const Node * dead_branch_removal() const = 0;
  */
 
  //! Static functions for keeping xml indentation nice
  static void tab(bool open) {
    if (open) {
      tabcount++;
    } else {
      tabcount--;
    }
    std::cout << std::string(tabcount, '\t');
  }
  static void tab_incr() { tabcount++; }
  static void tab_decr() { tabcount--; }
  static void tab() { if (tabcount) std::cout << std::string(tabcount, '\t'); }
  static void change() { changed++; }
  int getChanged() { return changed; }
};

#endif
