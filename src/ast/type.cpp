/*
 * type.cpp
 *
 *
 */

#include <assert.h>
#include "ast/type.hpp"

Type::Type(int i) {
  if (i<0xC){
    t = i;
  }
  else if (i<0x51){
    q = i;
  }
  else {
    s = i;
  }
};

/* GETTERS */

unsigned Type::getType() const {
  return t;
}

std::string Type::getTypename() const {
  std::stringstream ss;  
    switch((Type_specifier)t){
      case None      :
        ss << "None";
        break; 
      case Int       : 
        ss << "Int";
        break; 
      case Void      : 
        ss << "Void";
        break; 
      case Char      : 
        ss << "Char";
        break; 
      case Float     : 
        ss << "Float";
        break; 
      case Double    : 
        ss << "Double";
        break;
      case LongDouble: 
        ss << "LongDouble";
        break;
      case Signed    : 
        ss << "Signed";
        break; 
      case Unsigned  : 
        ss << "Unsigned";
        break; 
      case Short     : 
        ss << "Short";
        break; 
      case Long      : 
        ss << "Long";
        break; 
      case LongLong  : 
        ss << "LongLong";
        break; 
    }
    return ss.str();
}

/* END OF GETTERS */

void Type::add(const Type* in) const {
  unsigned tin = in->getType();
  unsigned qin = in->getQ();
  unsigned stin= in->getS();
  if (qin){
    // Should only have one qualifier
    assert(q==0);
    q = qin; 
  }
  if (stin){
    // Should only have one specifier
    assert(s==0);
    s = stin;
  }
  if (t==0){
    // If Type has no type, just replace with new type
    t = tin;
  }
  
  else if (tin>6){
    // If type already has a type, check if new type is more specific
    // If it's an integer, replace with more specific type
    if (t==0x1){
      t = tin;
    }
    // If its a double, replace with more specific type
    else if (t==0x5){
      t = tin;
    }
    else if (t==Long){
      if (tin==Long){
        t==LongLong;
      }
    }
  }
  return;
}

void Type::setPtr() const {
  ptr = true;
}
