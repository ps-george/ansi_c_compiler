#include "codegen_helpers.hpp"
#include "iostream"
#include "stdexcept"

int UNIQ_GEN = 0;

void Context::addString(std::string s){
  if (bindings.count(s)){
      std::cerr << s <<" is already in strbindings, do nothing" << std::endl;
  }
  else{
    std::string str_loc = "$LC"+getUnq();
    strbindings[s] = str_loc;
  }
}
std::string Context::getString(std::string s){
  return strbindings.at(s);
}

void Context::createStrings(){
  for (auto const& s: strbindings){
    ss() << s.second << ":" << std::endl;
    ss() << "\t.ascii\t" << "\""+s.first+"\\000\"" << std::endl;
    ss() << "\t.align\t2" << std::endl;
  }
}

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

void Context::assignVariable(std::string id, std::string type, int offin){
  bindings[id] = Var{1,type,offin};
}

int store(Context& ctxt, std::string id, int d){
  try{
    ctxt.ss() << "\tsw\t$" << d <<"," << ctxt.getVariable(id) << "($fp)" << " # store back in the same place" << std::endl;
  }
  catch (std::exception& e){
    std::cerr << e.what();
    return 1;
  }
  return 0;
}


std::string makeLabel(std::string base){
  base = base + std::to_string(UNIQ_GEN++);
  return base;
}

std::string getUnq() {
  return std::to_string(UNIQ_GEN++);
}

void Context::push(int reg){
  ss() <<"### PUSH\n\taddi\t$sp,$sp,-4" << std::endl;
  ss() << "\tsw\t$" <<reg <<",0($sp)\n" << std::endl;
}

void Context::pop(int reg){
  ss() << "### POP\n\tlw\t$" <<reg<< ",0($sp)" << std::endl;
  ss() <<"\taddi\t$sp,$sp,4\n" << std::endl;
}
