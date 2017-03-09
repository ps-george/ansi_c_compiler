/*
 * function.cpp
 *
 *
 */

#include "ast/function.hpp"

//! Constructor
Function::Function(const Node *_type, const Node *_dec, const Node *_s)
    : declarator(new Declaration((const Type *)_type, (const List *)_dec))  ,
      stat((const CompoundStatement *)_s) {};

/*
 * GETTERS
 */
std::vector<const Node *> Function::getChildren() const{
  //  std::cerr << "Finding children of " << declarator->getId() << ":" << std::endl;
  return {declarator, stat};
}

std::string Function::getType() const { return declarator->getTypename(); }

std::string Function::getHeader() const {
  return "<" + getNodeType() 
             + " id=\"" + declarator->getId() 
             + "\" type=\"" + getType()
             + "\" " + getDeets()
             + " >";
}

/*
 * END OF GETTERS
 */

/* PRINT ASM */

void Function::print_asm(Context& ctxt) const{
  std::vector<std::string> vars = getChildDefs();
  int vars_size = vars.size()*4;
  // std::cerr << vars_size << std::endl;
  // Indicated that we're printing out a function
  std::string fname = declarator->getId();
  //ctxt.ss() << "# Function " << fname << std::endl;
  //ctxt.ss() << "### Preamble" << std::endl;
  ctxt.ss() << "\t.globl\t" << fname	<< "\n\t.set	nomips16\n\t.set	nomicromips\n\t.ent\t" << fname	<< "\n\t.type\t" << fname <<", @function\n";
  ctxt.setF(fname);
  
  // Stack grows upwards
  /* Preamble */
  // Label for the function
  ctxt.ss() << fname << ":" << std::endl
  // Print the frame: we need vars+8 as frame size because
  // we store the previous frame pointer and return address
  << "\t.frame\t$fp,"<< vars_size+8 << ",$31\t\t# vars= "<< vars_size <<", regs= 1/0, args= 0, gp= 0" << std::endl
  
  // If there are function calls with the function, have to do preamble differently
  // .mask has something to do with int size
  << "\t.mask\t0x40000000,-4" << std::endl
  // .fmask has something to do with float size
  << "\t.fmask\t0x00000000,0" << std::endl
  // Don't know why these are here yet
  << "\t.set\tnoreorder" << std::endl
  << "\t.set\tnomacro" << std::endl
  
  // Reserve space on the stack for the frame
  << "\taddiu\t$sp,$sp,-" << vars_size+8 << std::endl
  // Store the previous frame pointer
  << "\tsw\t$fp,"<< vars_size+4 << "($sp)" << std::endl
  // Write new frame pointer as current stack pointer
  << "\tmove\t$fp,$sp" << std::endl;
  // ctxt.ss() << "### End of preamble" << std::endl;
  /* Print asm for the function */
  // Remember to set return register ($2) to return value
  Node::print_asm(ctxt);
  
  /* POSTAMBLE */
  // When we hit a jump statement
  // ctxt.ss() << "### Postamble" << std::endl;
  ctxt.ss() << declarator->getId() << "postamble:" << std::endl;
  // Move the frame pointer to stack pointer
  ctxt.ss() << "\tmove $sp,$fp" << std::endl
  // Load the previous frame pointer (unwind)
  << "\tlw\t$fp," << vars_size+4 <<"($sp)" << std::endl
  // Unallocate the frame we were in
  << "\taddiu\t$sp,$sp," << vars_size+8 << std::endl
  // Return
  << "\tj\t$31\n\tnop" << std::endl << std::endl;
  
  ctxt.ss() << "\t.set\tmacro\n\t.set\treorder\n\t.end\t" << fname << "\n\t.size\t" <<	fname << ", .-" << fname << std::endl;
  // ctxt.ss() << "### End of postamble" << std::endl;
}

/* PRINT XML */
void Function::print_xml(std::ostream &stream) const {
  tab(stream,true);
  stream << getHeader() << std::endl;
  tab(stream); stream << "<!-- Function declarator -->" << std::endl;
  declarator->print_xml(stream);
  stat->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}


/* PRINT C */
// void Function::print_c() const { 
//  std::cout << getType() << " ";
//  declarator->print_c();
//  std::cout << "\n";
//  stat->print_c();
//}
