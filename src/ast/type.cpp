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

Type::Type(bool b) : sign(b) {};

/* GETTERS */

unsigned Type::getType() const {
  return t;
}

std::vector<std::string> Type::getTypeVec() const {
  std::vector<std::string> v;
  std::stringstream ss;
  switch((Type_specifier)t){
    case None      :
      v.push_back("None");
      break; 
    case Int       : 
      v.push_back("Int");
      break; 
    case Void      : 
      v.push_back("Void");
      break; 
    case Char      : 
      v.push_back("Char");
      break; 
    case Float     : 
      v.push_back("Float");
      break; 
    case Double    : 
      v.push_back("Double");
      break;
    case LongDouble: 
      v.push_back("LongDouble");
      break;
    case Short     : 
      v.push_back("Short");
      break; 
    case Long      : 
      v.push_back("Long");
      break; 
    case LongLong  : 
      v.push_back("LongLong");
      break; 
  }
  ss << std::hex << "0x" << s;
  ss.clear();
  ss << std::hex << "0x" << q << std::dec; 
  v.push_back(ss.str());
  v.push_back(ss.str());
  if (sign){
    v.push_back("Signed");
  } else {
    v.push_back("Unsigned");
  }
  return v;
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
  ss << std::hex << " 0x" << s;
  ss << std::hex << " 0x" << q << std::dec;
  
  if (sign){
    ss << " Signed";
  } else {
    ss << " Unsigned";
  }
  return ss.str();
}

/* END OF GETTERS */

void Type::add(const Type* in) const {
  unsigned tin = in->getType();
  unsigned qin = in->getQ();
  unsigned stin= in->getS();
  bool signin = in->getSign();
  
  // If sign is true, can always overwrite
  if (sign){
    sign = signin;
  }
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
        t=LongLong;
      }
    }
  }
  return;
}

void Type::setPtr() const {
  ptr = true;
}
