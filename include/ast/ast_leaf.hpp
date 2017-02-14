#ifndef ast_leaf_hpp
#define ast_leaf_hpp

#include <iostream>
#include <vector>
#include <string>

class Leaf {
private:
  static int tabcount;
  static int changed;

public:
  virtual ~Leaf() {}
  //! For recursive print_xml function
  virtual void print_xml() const = 0;

  //! For getting xml indentation correct
  static void tab(bool open) {
    if (open) {
      tabcount = tabcount + 1;
    } else {
      tabcount = tabcount - 1;
    }
    // std::cout << tabcount;
    std::cout << std::string(tabcount, '\t');
  }
  
  virtual std::vector<const Leaf *> getAllStems() const = 0;
  
  virtual std::string getType() const { return "Leaf"; }
  
  /* For fixed point shrink tree algorithm, useful for mathematical Expressions

  virtual const Leaf *shrink() const =0;
  static void change() {
    changed++;
  }

  static void reset_changed() {
    changed = 0;
  }

  static int has_changed() {
    return changed;
  }
  */
  void tab() const { std::cout << std::string(tabcount, '\t'); }
};

#endif
