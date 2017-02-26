#include "codegen_helpers.hpp"

std::string Context::getVariable(std::string id){
  
};

std::ostream& Context::ss(){
  return *out;
};

void Context::assignVariable(std::string id, std::string type, int value){
  bindings[id] = Var({1,2,1});
}

void generic_instruction(Context ctxt, ...){
  // x = y
  // start from the right hand side
  // Get a free register
  // std::string reg = getRegister();
  
  // Store the right in that register
  // If the right is a variable, 
  
  // If the left is 
  
}
