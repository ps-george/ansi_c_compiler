#ifndef VARIABLE_HPP_
#define VARIABLE_HPP_

#include "expression.hpp"
#include "type.hpp"

#include <sstream>

class Variable : public Expression {
private:
  std::string id;
  mutable const Type * type;
  mutable int ptr = 0;
  // Variable will have a type
public:
  virtual ~Variable(){};

  Variable(const std::string* _id, const Type * t) : id(*_id), type(t) {};
  Variable(const std::string* _id) : id(*_id) { type = new Type(Int);};
  Variable(const std::string* _id, const Type * t, bool p) : id(*_id), type(t), ptr(p) {};
  Variable(const std::string* _id, bool p) : id(*_id), ptr(p) { type = new Type(Int);};
  
  virtual std::string getType() const;
  virtual std::vector<std::string> getTypeVec() const;
  virtual std::string getNodeType() const override;
  virtual std::string getId() const override;
  virtual std::string getHeader() const override;
  void setPtr() const { ptr++; }
  int getPtr() const { return ptr; }
  virtual void print_xml(std::ostream &stream) const override;
  virtual Context print_asm(Context ctxt, int d = 2) const override;
  // virtual void print_c() const override;
};

class Parameter : public Variable {
public:
  virtual ~Parameter(){};
  Parameter(const std::string* _id, const Type * t) : Variable(_id, t) {}
  Parameter(const std::string* _id) : Variable(_id) {}
  virtual std::string getNodeType() const override;
};

#endif
