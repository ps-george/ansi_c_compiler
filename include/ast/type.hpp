#ifndef TYPE_HPP_
#define TYPE_HPP_

#include "node.hpp"

#include <sstream>
#include <string>
#include <vector>


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
class TypeSpecifier : public Node {
private:
  std::string name;
public:
  TypeSpecifier(std::string* n) : name(*n) {};
  virtual std::string getNodeType() const { return "TypeSpecifier"; };
};

/*! \brief A type is a primitive
 *
 */
class Type : public Node {
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
  virtual std::string getNodeType() const { return "Type"; };
};

#endif
