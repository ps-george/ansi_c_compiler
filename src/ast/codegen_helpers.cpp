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

int Context::getVarOffset(std::string id){
  return bindings.at(id).offset;
}

void Context::loadVariable(std::string id, int d){
  Var v = getVariable(id);
  if (v.glob){
    ss() << "\tlui\t$28,%hi(__gnu_local_gp)" << std::endl;
    ss() << "\taddiu\t$28,$28,%lo(__gnu_local_gp)" << std::endl;
    ss() << "\tlw\t$" << d << ",%got(" << id <<")($28)" <<std::endl;
    ss() << "\tlw\t$" << d << ",0($2)" << std::endl;
  } else {
    ss() << "\tlw $" << d << "," << v.offset << "($fp)" << " # load var: " << id << std::endl;
  }
  return;
};

void Context::loadVariable(std::string id, int d, bool array){
  Var v = getVariable(id);
  if (v.glob){
    ss() << "\tlui\t$28,%hi(__gnu_local_gp)" << std::endl;
    ss() << "\taddiu\t$28,$28,%lo(__gnu_local_gp)" << std::endl;
    ss() << "\tlw\t$" << d << ",%got(" << id <<")($28)" <<std::endl;
    ss() << "\tlw\t$" << d << ",0($2)" << std::endl;
  } else if (array) {
    // Array thingy will be in $8
    ss() << "\tli\t$9,4"<< std::endl;
    ss() << "\tmul $8,$8,$9" << std::endl;
    ss() << "\taddiu $8,$8," << v.offset << std::endl;
    ss() << "\taddu $8,$fp,$8" << std::endl;
    ss() << "\tlw $" << d << ",0($8)" << " # load var: " << id << std::endl;
  }
  else {
    ss() << "\tlw $" << d << "," << v.offset << "($fp)" << " # load var: " << id << std::endl;
  }
  return;
};

Var Context::getVariable(std::string id){
  if (bindings.count(id))
    return bindings.at(id);
  else {
    // If can't find it, assume global
    return Var{0,"Int",0,true,false};
  }
}

void Context::storeVariable(std::string id, int d){
  Var v = getVariable(id);
  ss() << "\t# " << v.type << std::endl;
  if (v.glob){
    ss() << "\t#global variable " << id << std::endl;
    // Store the variable going into global in $17
    ss() << "\tmove\t$17,$" << d << std::endl;
    // Load these shizzle into $2
    ss() << "\tlui\t$28,%hi(__gnu_local_gp)" << std::endl;
    ss() << "\taddiu\t$28,$28,%lo(__gnu_local_gp)" << std::endl;
    ss() << "\tlw\t$2,%got(" << id <<")($28)" <<std::endl;
    // Store 17 into the thingy
    ss() << "\tsw\t$17,0($2)" << std::endl;
  } else if (v.arr) {
    // Array thingy will be in $8
    ss() << "\tli\t$9,4"<< std::endl;
    ss() << "\tmul $8,$8,$9" << std::endl;
    ss() << "\taddiu $8,$8," << v.offset << std::endl;
    ss() << "\taddu $8,$fp,$8" << std::endl;
    ss() << "\tsw $" << d << ",0($8)" << " # load var: " << id << std::endl;
  } else {
    ss() << "\tsw\t$" << d <<"," << v.offset << "($fp)" << " # store var: " << id << std::endl;
  }
  return;
}

std::ostream& Context::ss(){
  return *out;
};

void Context::assignVariable(std::string id, std::string type){
  bindings[id] = Var{1,type,offset,0,false};
  offset+=4;
}

void Context::assignVariable(std::string id, std::string type, int offin){
  bindings[id] = Var{1,type,offin,0,false};
}

void Context::assignVariable(std::string id, std::string type, bool glob){
  if (glob){
    //ss() << "\t.comm\t" << id << ",4,4" << std::endl;
    bindings[id] = Var{1,type,0,true,false};
  }
}

void Context::assignVariable(std::string id, std::string type, bool glob, bool arr){
  bindings[id] = Var{1,type,0,glob,arr};
}

std::string makeLabel(std::string base){
  base = base + std::to_string(UNIQ_GEN++);
  return base;
}

std::string getUnq() {
  return std::to_string(UNIQ_GEN++);
}

void Context::push(int reg){
  ss() <<"### PUSH\n\taddiu\t$sp,$sp,-4" << std::endl;
  ss() << "\tsw\t$" <<reg <<",0($sp)\n" << std::endl;
}

void Context::pop(int reg){
  ss() << "### POP\n\tlw\t$" <<reg<< ",0($sp)" << std::endl;
  ss() <<"\taddiu\t$sp,$sp,4\n" << std::endl;
}
