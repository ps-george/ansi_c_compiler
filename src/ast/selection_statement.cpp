/*
 * selection_statement.cpp
 *
 *
 */

#include "ast/selection_statement.hpp"
#include "codegen_helpers.hpp"

/*
 * GETTERS
 */

std::string IfStatement::getNodeType() const {
  if (parser)
    return "Scope";
  return "IfStatement";
}

std::string IfElseStatement::getNodeType() const {
  if (parser)
    return "Scope";
  return "IfElseStatement";
}

std::string SwitchStatement::getNodeType() const {
  return "SwitchStatement";
}


const Expression *SelectionStatement::getCondition() const { return getConditions()[0]; };

std::vector<const Expression *>SelectionStatement::getConditions() const {
  return {cond};
}

/*
 * END OF GETTERS
 */

 /*
  * PRINT ASM
  */

Context SwitchStatement::print_asm(Context ctxt, int d) const {
  // Don't want to pass context laterally across scope
  Context t_ctxt = ctxt;
  
  // Set the break to then end of this statement
  std::string switchend = "switchend" + getUnq();
  t_ctxt.setBreak(switchend);
  
  // Evaluate condition into register 2
  cond->print_asm(t_ctxt);
  
  // Print out the statement
  getBody()->print_asm(t_ctxt);
  
  // Go here if there is a break
  ctxt.ss() << switchend << ":" << std::endl << "\tnop" << std::endl;
  
  return ctxt;
};

Context IfElseStatement::print_asm(Context ctxt, int d) const {
  ctxt.ss() << "## " << getNodeType() << std::endl;
  std::string uq_num = getUnq();
  std::string ifend = "$ifend" + uq_num;
  std::string ifstart = "$ifstart" + uq_num;
  
  getCondition()->print_asm(ctxt);
  ctxt.ss() << "\tbne $2,$0," << ifstart << std::endl;
  ctxt.ss() << "\tnop" << std::endl;
  // Do statement 2 and jump to endl
  ctxt = stat2->print_asm(ctxt);
  ctxt.ss() << "\tb " << ifend << std::endl;
  ctxt.ss() << "\tnop" << std::endl;

  // do statement 1
  ctxt.ss() << ifstart << ":" << std::endl;
  ctxt = stat1->print_asm(ctxt);
  ctxt.ss() << ifend << ":" << std::endl;
  return ctxt;
}


/*
 * PRINT XML
 */

void IfStatement::print_xml(std::ostream &stream) const {
  tab(stream,true);
  stream << getHeader() << std::endl;
  if (!parser){
    tab(stream);
    stream << " <!-- If -->" << std::endl;
    tab(stream,true);
      stream << "<Condition>" << std::endl;
          getCondition()->print_xml(stream);
      tab(stream,false);
      stream << "</Condition>" << std::endl;
      tab(stream,true);
      stream << "<Then>" << std::endl;
    }
    stat1->print_xml(stream);
  if (!parser){
    tab(stream,false);
    stream << "</Then>" << std::endl;
  }
  tab(stream,false);
  stream << getFooter() << std::endl;
}

void IfElseStatement::print_xml(std::ostream &stream) const {
  IfStatement::print_xml(stream);
  tab(stream);
  stream << getHeader() << std::endl;
  
  if (!parser){
    tab(stream);
    stream << " <!-- Else -->" << std::endl;
  }
  tab_incr();
  stat2->print_xml(stream);
  tab(stream,false);
  stream << getFooter() << std::endl;
}
/*
 * END OF PRINTERS
 */
