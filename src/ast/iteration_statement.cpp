/*
 * iteration_statement.cpp
 *
 *
 */

#include "ast/iteration_statement.hpp"
#include "codegen_helpers.hpp"

std::string IterationStatement::getNodeType() const { 
  if (parser)
    return "Scope";
  return "IterationStatement"; }
std::string ForStatement::getNodeType() const { 
  if (parser)
    return "Scope";
  return "ForStatement"; }
std::string WhileStatement::getNodeType() const { 
  if (parser)
    return "Scope";
  return "WhileStatement"; }
std::string DoWhileStatement::getNodeType() const { 
  if (parser)    
    return "Scope";
  return "DoWhileStatement"; }

/*
 * GETTERS
 */

std::vector<const Node*> WhileStatement::getChildren() const {
  return {cond,stat1};
}

std::vector<const Node*> ForStatement::getChildren() const {
  return {cond1,stat1};
}

std::vector<const Node*> EEForStatement::getChildren() const {
  return {cond1,cond2,stat1};
}

std::vector<const Node*> EEEForStatement::getChildren() const {
  return {cond1,cond2,cond3,stat1};
}

std::vector<const Node*> DEForStatement::getChildren() const {
  return {dec,cond1,stat1};
}

std::vector<const Node*> DEEForStatement::getChildren() const {
  return {dec,cond1,cond2,stat1};
}

/*
 * END OF GETTERS
 */

/*
 * PRINTERS
 */

Context print_while(Context ctxt, const Expression * cond, const Statement * stat1, std::string type){
  // Create labels
  std::string uq_num = getUnq();
  std::string condlabel = "$cond" + uq_num;
  std::string whilestart = "$whilestart" + uq_num;
  std::string whilend = "$whilend" + uq_num;
  
  if (type=="DoWhile"){
    // Go through while loop once first
    ctxt.ss() << "\tb\t" << whilestart << std::endl;
  }
  
  // label for condition
  ctxt.ss() << condlabel << ":" << std::endl;
  cond->print_asm(ctxt,2);
  // If condition is 0, go to end
  ctxt.ss() << "\tbeq\t$2,$0," << whilend << std::endl;
  ctxt.ss() << "\tnop" << std::endl;
  // Do the statment
  ctxt.ss() << whilestart << ":" << std::endl;
  ctxt = stat1->print_asm(ctxt);
  ctxt.ss() << "\tb\t" << condlabel << std::endl;
  ctxt.ss() << "\tnop" << std::endl;
  ctxt.ss() << whilend << ":" << std::endl;
  return ctxt;
}

Context WhileStatement::print_asm(Context ctxt, int d) const {
  return print_while(ctxt, getConditions().at(0), stat1, "While");
}

Context DoWhileStatement::print_asm(Context ctxt, int d) const {
  return print_while(ctxt, getConditions().at(0), stat1, "DoWhile");
}

Context ForStatement::print_asm(Context ctxt, int d) const {
  return ctxt;
  // return print_while(ctxt, getConditions().at(0), stat1, "For");
}



/*
void DEForStatement::print_xml(std::ostream& stream) const {
  tab(stream);
  stream << getHeader() << std::endl;
  tab_incr();
  dec->print_xml(stream);
  stat1->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}
*/

/*
 * END OF PRINTERS
 */

// void IterationStatement::print_c() const { 
  // while ()
//  std::cout << getNodeType() << " (";
//  for (auto &it : getConditions()) {
//    it->print_c();
//  }
//  std::cout << ")\n";
//  tab();
//  getBody()->print_c();
//};
