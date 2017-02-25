#ifndef VARIABLE_HPP_
#define VARIABLE_HPP_

#include "expression.hpp"
#include "type.hpp"

#include <sstream>

class Variable : public Expression {
private:
  std::string id;
  const Type * type;
  // Variable will have a type
public:
  virtual ~Variable(){};

  Variable(const std::string* _id, const Type * t) : id(*_id), type(t) {};
  Variable(const std::string* _id) : id(*_id) { type = nullptr;};
  
  virtual std::string getType() const { return type->getTypename(); }
  virtual std::string getNodeType() const override { return "Variable"; }
  virtual std::string getId() const override { return id; };
  virtual std::string getHeader() const override { return "<" + getNodeType() + " id=\"" + getId() + "\" />";
  }
  virtual void print_xml() const override;
};

class Parameter : public Variable {
public:
  virtual ~Parameter(){};
  Parameter(const std::string* _id, const Type * t) : Variable(_id, t) {}
  Parameter(const std::string* _id) : Variable(_id) {}
  virtual std::string getNodeType() const override { return "Parameter"; }
};

#endif
