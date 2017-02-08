#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

class Expression
{
private:
  static int tabcount;
  static int changed;
public:
    virtual ~Expression()
    {}

    virtual void print_xml() const =0;
    
    // virtual const Expression *shrink() const =0;
    
    static void tab(bool open) {
      if (open){
        tabcount = tabcount + 1;
      }
      else {
        tabcount = tabcount - 1;
      }
      //std::cout << tabcount;
      std::cout << std::string(tabcount,'\t');
      
    }
    
    static void change() {
      changed++;
    }
    
    static void reset_changed() {
      changed = 0;
    }
    
    static int has_changed() {
      return changed;
    }
    
    void tab() const {
      std::cout << std::string(tabcount,'\t');
    }
};

#endif
