#include "codegen_helpers.hpp"

int Context::getVariable(std::string id){
  return bindings.at(id).offset;
};

std::ostream& Context::ss(){
  return *out;
};

void Context::assignVariable(std::string id, std::string type){
  bindings[id] = Var{1,type,offset};
  offset+=4;
}
