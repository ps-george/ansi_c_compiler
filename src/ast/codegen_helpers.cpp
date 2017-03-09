#include "codegen_helpers.hpp"
#include "iostream"
#include "stdexcept"


int Context::getVariable(std::string id){
  return bindings.at(id).offset;
};

std::ostream& Context::ss(){
  return *out;
};

void Context::assignVariable(std::string id, std::string type){
  if (bindings.count(id)){
      //  std::cerr << "Already in bindings, shadow now." << std::endl;
  }
  bindings[id] = Var{1,type,offset};
  offset+=4;
}

int store(Context& ctxt, std::string id){
  try{
    ctxt.ss() << "\tsw\t$2," << ctxt.getVariable(id) << "($fp)" << " # store back in the same place" << std::endl;
  }
  catch (std::exception& e){
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
