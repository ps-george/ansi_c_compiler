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

//! Probably will implement
enum Type_specifier {
  None     = 0x0,
  Int      = 0x1,
  Void     = 0x2,
  Char     = 0x3,
  Float    = 0x4,
  Double   = 0x5,
  LongDouble =0x6,
  Signed   = 0x7,
  Unsigned = 0x8,
  Short    = 0x9,
  Long     = 0xA,
  LongLong = 0xB
  
};


//! Probably won't implement!

enum Storage_specifier {
  //! One of:
  Auto    = 0x10,
  Extern  = 0x20,
  Static  = 0x30,
  Typedef = 0x40,
  Register= 0x50
};

enum Type_qualifier {
  //! One of:
  Const    = 0x100, //! May implement
  Volatile = 0x200 //! Won't implement
};

//! struct-or-union-specifier, enum-specifier, typdef-name (if in list that needs to be built during parsing)

/*! \brief A type is a primitive
 *
 */
class Type : public Node {
  mutable unsigned t = 0x1; //! void, char, int, float, double defaults to int
  mutable unsigned q = 0; //! Default no qualifiers
  mutable unsigned s = 0; //! Default no specifiers
  
  mutable bool ptr = false;
public:
  Type(int i);
  
  void add(const Type* in) const;
  
  
  virtual unsigned getType() const;
  virtual std::string getTypename() const;
  virtual std::string getNodeType() const { return "Type"; };
  unsigned getQ() const { return q; }
  unsigned getS() const { return s; }
  void setPtr() const;
};

#endif
