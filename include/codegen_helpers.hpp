/*
 * codegen_helpers.hpp
 * 
 */

#ifndef CODEGEN_HELPERS_HPP_
#define CODEGEN_HELPERS_HPP_

extern int UNIQ_GEN;

class Node;

#include <map>
#include <stdio.h>
#include "ast/node.hpp"

std::string makeLabel(std::string base);
std::string getUnq();

struct Var {
  // A variable has an address, a register value if it's in a register, dirty flag if it shouldn't be spilled,
  int reg;
  std::string type;
  int offset;
  bool glob;
  bool ptr;
  // bool dirty
};

class Context {
private:
  std::map<std::string, Var> bindings;
  std::map<std::string, std::string> strbindings;
  std::ostream *out;
  int offset = 0;
  //int unique = 0;
  std::string f = "";
  std::string b = "";
  std::string c = "";
  //std::string cs = "";
public:
  Context(std::ostream *stream) { out = stream; };
  std::ostream& ss();
  
  void assignVariable(std::string id, std::string type);
  void assignVariable(std::string id, std::string type, int offin);
  void assignVariable(std::string id, std::string type, bool glob);
  void assignVariable(std::string id, std::string type, bool glob, bool ptr);
  void setVarPtr(std::string id);
  int isPtr(std::string id);
  
  Var getVariable(std::string id);
  void loadVariable(std::string id, int d);
  void storeVariable(std::string id, int d = 2);
  void storeVariable(std::string id, int s, int d);
  std::string getVarType(std::string id);
  int getVarOffset(std::string id);
  
  void addString(std::string s);
  std::string getString(std::string s);
  void createStrings();
  
  // Control flow statements - hacky but robust and quick solution
  // Return
  void setF(std::string fname){ f = fname; }
  std::string getF(){ return f; }
  // Break
  void setBreak(std::string exitlabel) { b = exitlabel; }
  std::string getBreak() { return b; }
  // Continue
  void setContinue(std::string startlabel) { c = startlabel; }
  std::string getContinue() { return c; }
  // Set offset
  void setOffset(int i){ offset = i;}
  int getOffset() { return offset; }
  int getAddress(const Node * in, int d =2);
  //void setSwitch(std::string sw) {cs = sw; }
  //std::string getSwitch() { return cs; }
  
  void push(int reg);
  void pop(int reg);
};


// For a scope:
// 1. Set up a frame pointer for the function
// # vars = n initalisations * 4
// addiu $sp, $sp, -(vars+8)
// sw $fp, (vars + 4)($sp)
// move $fp, $sp
// 2. For each variable initialised:
// li $2, 1 # Load the right hand side into a register
// sw $2,offset($fp) # store the variable in the frame, 
//                   # increment offset by 4 (starts at 0)
//                   # store the offset somewhere so we know how to get the variable again
// 3. When we use a variable
// lw $2, offset($fp) # load the variable referring to the offset stored in bindings
// 
// 
// 
// 
// 
// End of a function
// move $2, $0 #Load return value into register $2
// move $sp, $fp # move fp into sp
// lw $fp, vars+4($sp) # okay
// addiu $sp, $sp, vars+8
// j $31

// Things we need to be able to do:
// 1. Assign a variable
// 1a. Know which register contains the variable, or if not in a register
// 1b. Know whether the variable is in memory or not (and where in memory it is)
// 1c. Keep track of scope
// 1d. Keep track of shadow variables
// 2. Get a free register
// 2a. 

#endif
