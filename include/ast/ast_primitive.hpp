#ifndef AST_PRIMITIVE_HPP_
#define AST_PRIMITIVE_HPP_

#include "ast_expression.hpp"
#include "ast_list.hpp"
#include "ast_node.hpp"

#include <sstream>

// Primitives

class Primitive : public Node {
public:
  virtual ~Primitive(){};

  virtual std::string getNodeType() const override = 0;

  virtual std::string getHeader() const override {
    return "<" + getNodeType() + "\" />";
  }

  virtual void print_xml() const override {
    tab();
    std::cout << getHeader() << "\n";
  }
};

/*! \brief A TypeSpecifier is a primitive
 *
 * Can be: void, char, short, int, long, float
 * double, signed, unsigned, struct-or-union-specifier
 * enum-specifier, typdef-name (if in list of typedefs)
 *Constraints

Each list of type specifiers shall be one of the following sets; the type
specifiers may occur in any order, possibly intermixed with the other
declaration specifiers.
 * void
 * char
 * signed char
 * unsigned char
 * short , signed short , short int , or signed short int
 * unsigned short , or unsigned short int
 * int , signed , signed int , or no type specifiers
 * unsigned , or unsigned int
 * long , signed long , long int , or signed long int
 * unsigned long , or unsigned long int
 * float
 * double
 * long double
 * struct-or-union specifier
 * enum-specifier
 * typedef-name
 *
 */
class TypeSpecifier : public Primitive {
private:
  std::string name;
public:
  TypeSpecifier(std::string* n) : name(*n) {};
  virtual std::string getNodeType() const override { return "TypeSpecifier"; };
};

/*! \brief A type is a primitive
 *
 */
class Type : public Primitive {
  std::vector<TypeSpecifier *>
      type_specifiers; //! void, char, short, int, long, float
                       //! double, signed, unsigned, struct-or-union-specifier
                       //! enum-specifier, typdef-name (if in list of typedefs)
  // std::string storage_class_specifier;      //! One of: typedef, extern, static,
                                            //! auto, register
  // std::vector<std::string> type_qualifiers; //! const or volatile
public:
  Type(std::vector<TypeSpecifier *> tspecs) : type_specifiers(tspecs){};
  virtual std::string getTypename() const { 
    std::stringstream s; 
    for (auto i: type_specifiers)
      s << i << ' '; 
    return s.str(); 
  }
  virtual std::string getNodeType() const override { return "Type"; };
};

class Variable : public Expression {
private:
  std::string id;
  const Type * type;
  // Variable will have a type
public:
  virtual ~Variable(){};

  Variable(const std::string &_id, const Type * t) : id(_id), type(t) {};
  Variable(const std::string &_id) : id(_id) { type = nullptr;};
  
  virtual std::string getType() const { return type->getTypename(); }
  virtual std::string getNodeType() const override { return "Variable"; }

  virtual std::string getHeader() const override {
    return "<" + getNodeType() + " id=\"" + id + "\" />";
  }
};

class Parameter : public Variable {
public:
  virtual ~Parameter(){};
  Parameter(const std::string &_id, const Type * t) : Variable(_id, t) {}
Parameter(const std::string &_id) : Variable(_id) {}
  virtual std::string getNodeType() const override { return "Parameter"; }
};

//! Abstract base class for constant
class Constant : public Expression {
private:
  std::string valstr;
  // Constant will have a type as well`
public:
  virtual ~Constant(){};
  explicit Constant(const std::string &_valstr) : valstr(_valstr){};

  virtual std::string getNodeType() const override { return "Constant"; }

  virtual std::string getValue() const { return valstr; };
  virtual std::string getHeader() const override {
    return "<" + getNodeType() + " value=\"" + valstr + "\" />";
  }
  virtual void print_cpp() const override;
};

class StringLiteral : public Constant {
public:
  virtual ~StringLiteral(){};
  using Constant::Constant;
  std::string getNodeType() const override { return "StringLiteral"; };
};

class FloatConstant : public Constant {
private:
  float val;

public:
  virtual ~FloatConstant(){};

  FloatConstant(const std::string &_valstr) : Constant(_valstr) {
    val = std::stof(_valstr);
  };

  virtual std::string getNodeType() const override { return "float"; }
};

class DoubleConstant : public Constant {
private:
  double val;

public:
  virtual ~DoubleConstant(){};

  DoubleConstant(const std::string &_valstr) : Constant(_valstr) {
    val = std::stod(_valstr);
  };

  virtual std::string getNodeType() const override { return "double"; }
};

class IntConstant : public Constant {
private:
  int val;

public:
  virtual ~IntConstant(){};
  IntConstant(const std::string &_valstr) : Constant(_valstr) {
    val = std::stoi(_valstr);
  };

  virtual std::string getNodeType() const override { return "int"; }
};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {
  virtual ~EnumConstant(){};
};

class CharConstant : public Constant {
  virtual ~CharConstant(){};
};

#endif
