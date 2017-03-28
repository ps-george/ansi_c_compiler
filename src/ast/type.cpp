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
    case None:
      v.push_back("none");
      break; 
    case Int: 
      v.push_back("int");
      break; 
    case Void: 
      v.push_back("void");
      break; 
    case Char: 
      v.push_back("char");
      break; 
    case Float: 
      v.push_back("float");
      break; 
    case Double: 
      v.push_back("double");
      break;
    case LongDouble: 
      v.push_back("longdouble");
      break;
    case Short: 
      v.push_back("short");
      break; 
    case Long: 
      v.push_back("long");
      break; 
    case LongLong: 
      v.push_back("longlong");
      break; 
  }
  ss << std::hex << "0x" << s;
  ss.clear();
  ss << std::hex << "0x" << q << std::dec; 
  v.push_back(ss.str());
  v.push_back(ss.str());
  if (sign){
    v.push_back("signed");
  } else {
    v.push_back("unsigned");
  }
  return v;
}

std::string Type::getTypename() const {
  std::stringstream ss;
  switch((Type_specifier)t){
    case None      :
      ss << "none";
      break; 
    case Int       : 
      ss << "int";
      break; 
    case Void      : 
      ss << "void";
      break; 
    case Char      : 
      ss << "char";
      break; 
    case Float     : 
      ss << "float";
      break; 
    case Double    : 
      ss << "double";
      break;
    case LongDouble: 
      ss << "longdouble";
      break;
    case Short     : 
      ss << "short";
      break; 
    case Long      : 
      ss << "long";
      break; 
    case LongLong  : 
      ss << "longlong";
      break; 
  }
  ss << std::hex << " 0x" << s;
  ss << std::hex << " 0x" << q << std::dec;
  
  if (sign){
    ss << " signed";
  } else {
    ss << " unsigned";
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
