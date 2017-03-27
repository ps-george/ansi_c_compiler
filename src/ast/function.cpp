/*
 * function.cpp
 *
 *
 */

#include "ast/function.hpp"

//! Constructor
//! 
// std::string id; //! Can get from declarator->getId()
// const List * params; //! Can get from declarator->getParams()
// 
Function::Function(const Node *_type, const Node *_dec, const Node *_s)
    : type((const Type *)_type),
      declarator((const FunctionDeclarator *)_dec),
      stat((const CompoundStatement *)_s) {
        id = declarator->getId(); //! Returns id of first child, won't have declaration lists of functions
      };

/*
 * GETTERS
 */
std::vector<const Node *> Function::getChildren() const{
  //  std::cerr << "Finding children of " << declarator->getId() << ":" << std::endl;
  return {stat};
}

std::string Function::getType() const { return type->getTypename(); }

std::string Function::getHeader() const {
  return "<" + getNodeType() 
             + " id=\"" + id 
             + "\" type=\"" + type->getTypename()
             + "\" " + getDeets()
             + " >";
}

std::string Function::getDeets() const {
  std::string params = getParamString();
  if (params!=""){
    params = "params=\"" + params + "\" ";
  }
  return params + Node::getDeets();
}

std::vector<std::string> Function::getParams() const {
  std::vector<std::string> out;
  for (auto it: declarator->getParams()->getChildren()){
    out.push_back(it->getId());
  }
  return out;
}

std::string Function::getParamString() const {
  std::string out;
  for (auto it: getParams()){
    out += it + ",";
  }
  if (out!=""){
    out = out.substr(0, out.size()-1);
  }
  return out;
}

/*
 * END OF GETTERS
 */

void Function::setChildDefs() const {
  Node::setChildDefs();
  //! Add params as child defs, could not do this and deal with parameters separately
}

/* PRINT ASM */

Context Function::print_asm(Context ctxt, int d) const{
  Context s_ctxt = ctxt;
  std::vector<std::string> vars = getChildDefs();
  int i = 0;
  std::vector<std::string> args = getChildParams();
  int args_size = 16;
  if (args.size()>0){
    for (auto &it: args){
      // ctxt.ss() << "# " << it << std::endl;
      if (i>3){
        args_size+=4;
      }
      i++;
    }
  }
  
  int vars_size = vars.size()*4 + getParams().size()*4;
  int pad = 0;
  int total_size = args_size+vars_size + 8;
  if (total_size%8!=0){
    // add padding
    pad = 4;
  }
  
  // Deal with parameters
  // Add parameters to context
  i = 0;
  
  // Set offset to local data area for local variables
  int local_offset = total_size+8-vars_size;
  ctxt.setOffset(local_offset);
  
  for (auto &it : getParams()){
    if (i==4){
      ctxt.setOffset(total_size+8+pad+16);
    }
    ctxt.ss() << "# param " << i << ": " << it << " \n";
    ctxt.assignVariable(it,"int");
    if (i<4){
      // Set the offset to after the frame to assign input arguments
      local_offset = ctxt.getOffset();
    }
    i++;
  }
  ctxt.setOffset(local_offset);
  // std::cerr << total_size << std::endl;
  // Indicated that we're printing out a function
  std::string fname = id;
  
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
  << "\t.frame\t$fp,"<< total_size+8+pad << ",$31\t\t# vars= "<< vars_size <<", regs= 1/0, args= " << args_size << ", gp= 0" << std::endl
  
  // If there are function calls with the function, have to do preamble differently
  // .mask has something to do with int size
  << "\t.mask\t0x40000000,-4" << std::endl
  // .fmask has something to do with float size
  << "\t.fmask\t0x00000000,0" << std::endl
  // Don't know why these are here yet
  << "\t.set\tnoreorder" << std::endl
  << "\t.set\tnomacro" << std::endl
  
  // Reserve space on the stack for the frame
  << "\taddiu\t$sp,$sp,-" << total_size+8+pad << std::endl
  
  // Store the previous return address
  << "\tsw\t$31,"<< total_size+4-vars_size << "($sp)" << std::endl
  
  // Store the previous frame pointer
  << "\tsw\t$fp,"<< total_size-vars_size << "($sp)" << std::endl
  
  // Store the previous result
  << "\tsw\t$16,"<< total_size-4-vars_size << "($sp)" << std::endl
  
  // Write new frame pointer as current stack pointer
  << "\tmove\t$fp,$sp" << std::endl;
  
  // Store parameters in the frame
  
  i = 4;
  for (auto &it : getParams()){
    if (i<8){
      // First four parameters $4,$5,$6,$7
      ctxt.ss() << "\tmove $2,$" << std::to_string(i++) << std::endl;
      store(ctxt, it);
    }
    // For the rest of the input parameters, they will be on the stack already
  }
  
  // ctxt.ss() << "### End of preamble" << std::endl;
  /* Print asm for the function */
  // Remember to set return register ($2) to return value
  ctxt = Node::print_asm(ctxt);
  
  /* POSTAMBLE */
  // When we hit a jump statement
  // ctxt.ss() << "### Postamble" << std::endl;
  ctxt.ss() << fname << "postamble:" << std::endl;
  // Move the frame pointer to stack pointer
  ctxt.ss() << "\tmove $sp,$fp" << std::endl
  
  // Load the previous return address
  << "\tlw\t$31," << total_size+4-vars_size <<"($sp)" << std::endl
  // Load the previous frame pointer (unwind)
  << "\tlw\t$fp," << total_size-vars_size <<"($sp)" << std::endl
  // Load the previous value in $16
  << "\tlw\t$16," << total_size-4-vars_size <<"($sp)" << std::endl
  // Unallocate the frame we were in
  << "\taddiu\t$sp,$sp," << total_size+8+pad << std::endl
  // Return
  << "\tj\t$31\n\tnop" << std::endl << std::endl;
  
  ctxt.ss() << "\t.set\tmacro\n\t.set\treorder\n\t.end\t" << fname << "\n\t.size\t" <<	fname << ", .-" << fname << std::endl;
  // ctxt.ss() << "### End of postamble" << std::endl;
  return s_ctxt;
}

/* PRINT XML */
void Function::print_xml(std::ostream &stream) const {
  tab(stream,true);
  stream << getHeader() << std::endl;
  tab(stream); stream << "<!-- Function declarator -->" << std::endl;
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
