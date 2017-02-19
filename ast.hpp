#include <iostream>
#include <string>
#include <vector>

//! Abstract base class for ast node
class Node {
private:
  static int tabcount;
  static int changed;
public:
  virtual ~Node();
  
  //! Return the type of the node
  virtual std::string getType() const = 0;
  
  //! Return the xml header for the node
  virtual std::string getHeader() const { return "<" + getType() + ">"; };
  
  //! Return the xml footer for the node
  virtual std::string getFooter() const { return "</" + getType() + ">"; };
  
  //! Return a vector containing all of the children of the node
  virtual std::vector<const Node *> getChildren() const = 0;
  
  //! Print out the xml for all of the node's children
  virtual void print_children() const {
    for (auto &it : getChildren()) {
      it->print_xml();
    }
  };
  
  //! Print xml implicit recursive function
  virtual void print_xml() const {
    tab();
    std::cout << getHeader() << std::endl;
    tab_incr();
    print_children();
    tab(0);
    std::cout << getFooter() << std::endl;
  };
  
  //virtual const Node * constant_fold() const = 0;
  //virtual const Node * constant_propagation() const = 0;
  //virtual const Node * dead_branch_removal() const = 0;
  
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

class List : public Node {
  //! Contains a vector of pointers to ast nodes
protected:
  mutable std::vector<const Node *> children;

public:
  //! Initialise using brace initializer new List({arg1, arg2, arg3})
  List(std::vector<const Node *> _children) : children(_children) {}
  
  //! Destructor for branch
  virtual ~List() {
    for (auto &it : children)
      delete it;
    children.clear();
  }
  
  // Print out all children on the same level -> Using list to store lists of things
  virtual void print_xml() const override {
      print_children();
  }
  
  virtual std::string getType() const override {
    return "List";
  };
  
};
//! Abstract base class for expressions
class Expression : public Node {
public:
  virtual std::string getType() const = 0;
};

//! Points to any number of expressions separated by commas
class ExpressionList : public Expression, public List {
public:
  ExpressionList(std::vector<const Node *> _children) : List(_children) {}
};

//! Unary expression points to one thing
class UnaryExpression : public Expression {
private:
  const Expression * child;
};

//! PostfixExpression
class PostfixExpression : public UnaryExpression {
private:
  
};

//! PrefixExpression
//! Referred to as UnaryExpression in the spec
//! 
class PrefixExpression : public UnaryExpression {
private:
};

//! Points to typename
class Sizeof : public UnaryExpression {
private:
};



//! AssignmentExpression has unaryExpression (left) followed by AssignmentExpression (right)

//! 
class TrinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * middle;
  const Expression * right;
};


class ConditionalExpression : public TrinaryExpression {
private:
};

class BinaryExpression : public Expression {
private:
  const Expression * left;
  const Expression * right;
};

//! AssignmentExpression: UnaryExpression assignment-op AssignmentExpression
class AssignmentExpression : public BinaryExpression {};

//! LORExpression: LORExpression || LANDExpression
class LORExpression : public BinaryExpression {};

//! LANDExpression: LANDExpression || ORExpression
class LANDExpression : public BinaryExpression {};

//! ORExpression: ORExpression | ANDExpression
class ORExpression : public BinaryExpression {};

//! ANDExpression: ANDExpression & EORExpression
class ANDExpression : public BinaryExpression {};

//! EORExpression: EORExpression ^ EqExpression
class EORExpression : public BinaryExpression {};

//! EqExpression: EqExpression EqOp RelExpression
class EqExpression : public BinaryExpression {};

//! RelExpression: RelExpression RelOp ShiftExpression
class RelExpression : public BinaryExpression {};

//! ShiftExpression: ShiftExpression ShiftOp AddExpression
class ShiftExpression : public BinaryExpression {};

//! AddExpression: AddExpression + SubExpression
class AddExpression : public BinaryExpression {};

//! SubExpression: SubExpression - MulExpression
class SubExpression : public BinaryExpression {};

//! MulExpression: MulExpression * DivExpression
class MulExpression : public BinaryExpression {};

//! DivExpression: DivExpression / ModExpression
class DivExpression : public BinaryExpression {};

//! ModExpression: ModExpression % CastExpression
class ModExpression : public BinaryExpression {};

//! Primary expression points to identifier, constant, StringLiteral or (expression)
class PrimaryExpression {
  
};

// Primitives

class StringLiteral {
  
};

//! Abstract base class for constant
class Constant : public Expression {
  
};

class FloatConstant : public Constant {
  
};

class IntConstant : public Constant {
  
};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {
  
};

class CharConstant : public Constant {
  
};
