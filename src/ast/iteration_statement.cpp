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
  
std::string EEForStatement::getNodeType() const { return "EEForStatement"; }
std::string DEForStatement::getNodeType() const { return "DEForStatement"; }
std::string EEEForStatement::getNodeType() const { return "EEEForStatement"; }
std::string DEEForStatement::getNodeType() const { return "DEEForStatement"; }



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

Context print_while(Context ctxt, const IterationStatement * in, const Statement * stat1){
  // Create labels
  std::string uq_num = getUnq();
  std::string condlabel = "$cond" + uq_num;
  std::string whilestart = "$whilestart" + uq_num;
  std::string whilend = "$whilend" + uq_num;
  
  std::string type = in->getNodeType();
  // Don't want to pass context laterally
  if (type=="EEForStatement" || type=="EEEForStatement"){
    // Want to do j=j+1 and update j
    ctxt = in->getChildren().at(0)->print_asm(ctxt,2);
  }
  Context t_ctxt = ctxt;
  if (type=="DEForStatement" || type=="DEEForStatement"){
    t_ctxt = in->getChildren().at(0)->print_asm(t_ctxt,2);
  }
  
  t_ctxt.setBreak(whilend);
  t_ctxt.setContinue(condlabel);
  
  if (type=="DoWhileStatement"){
    // Go through while loop once first
    ctxt.ss() << "\tb\t" << whilestart << std::endl;
  }
  
  // label for condition
  ctxt.ss() << condlabel << ":" << std::endl;
  if (type=="EEEForStatement" || type=="DEEForStatement"){
    in->getConditions().at(1)->print_asm(t_ctxt,2);
  }
  in->getConditions().at(0)->print_asm(t_ctxt,2);
  // If condition is 0, go to end
  ctxt.ss() << "\tbeq\t$2,$0," << whilend << std::endl;
  ctxt.ss() << "\tnop" << std::endl;
  // Do the statment
  ctxt.ss() << whilestart << ":" << std::endl;
  stat1->print_asm(t_ctxt);
  ctxt.ss() << "\tb\t" << condlabel << std::endl;
  ctxt.ss() << "\tnop" << std::endl;
  ctxt.ss() << whilend << ":" << std::endl;
  return ctxt;
}

Context IterationStatement::print_asm(Context ctxt, int d) const {
  print_while(ctxt, this, stat1);
  // Don't want to pass context laterally
  return ctxt;
}

/*
Context WhileStatement::print_asm(Context ctxt, int d) const {
  print_while(ctxt, this, stat1);
  // Don't want to pass context laterally
  return ctxt;
}

Context DoWhileStatement::print_asm(Context ctxt, int d) const {
  print_while(ctxt, this, stat1);
    // Don't want to pass context laterally
  return ctxt;
}

Context ForStatement::print_asm(Context ctxt, int d) const {
  return print_while(ctxt, this, stat1);
}

Context DEEForStatement::print_asm(Context ctxt, int d) const {
  return print_while(ctxt, this, stat1);
  // return print_while(ctxt, getConditions().at(0), stat1, "For");
}
*/


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
