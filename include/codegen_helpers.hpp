/*
 * codegen_helpers.hpp
 * 
 */

#ifndef CODEGEN_HELPERS_HPP_
#define CODEGEN_HELPERS_HPP_

#include <map>
#include <stdio.h>

struct Var {
  // A variable has an address, a register value if it's in a register, dirty flag if it shouldn't be spilled,
  int reg;
  uint32_t address;
  bool dirty;
};

class Context {
private:
  std::map<std::string, Var> bindings;
  std::ostream *out;
public:
  Context(std::ostream *stream) { out = stream; };
  std::ostream& ss();
  std::string getVariable(std::string id);
  void assignVariable(std::string id, std::string type, int value = 0);
  
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