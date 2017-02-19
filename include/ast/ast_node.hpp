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
  //virtual ~Node();
  
  //! Return the type of the node
  
  virtual std::string getType() const = 0;
  
  //! Return the xml header for the node
  virtual std::string getHeader() const { return "<" + getType() + ">"; };
  
  //! Return the xml footer for the node
  virtual std::string getFooter() const { return "</" + getType() + ">"; };
  
  virtual const Node * add(const Node* n) const {return this;};
  
  //! Return a vector containing all of the children of the node
  //virtual std::vector<const Node *> getChildren() const = 0;
  /*
  //! Print out the xml for all of the node's children
  virtual void print_children() const {
    for (auto &it : getChildren()) {
      it->print_xml();
    }
  };
  */
  //! Print xml implicit recursive function
  virtual void print_xml() const {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
    //print_children();
    tab(0);
    std::cout << getFooter() << std::endl;
  };
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
};

#endif
