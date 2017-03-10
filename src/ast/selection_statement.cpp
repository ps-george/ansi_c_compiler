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

Context IfElseStatement::print_asm(Context ctxt) const {
  ctxt.ss() << "## " << getNodeType() << std::endl;
  std::string ifend = makeLabel("ifend");
  std::string elsestart = makeLabel("elsestart");
  
  // Set $2 to 1 if 2>0, else $2=0
  ctxt.ss() << "\tslt $2,$0,$2" << std::endl;
  // If $2 is 0, do else condition
  ctxt.ss() << "\tbeq $2,$0," << elsestart << std::endl;
  // Do statement 1 and jump to endl
  ctxt = stat1->print_asm(ctxt);
  ctxt.ss() << "\tj " << ifend << std::endl
  << elsestart << ":" << std::endl;
  ctxt = stat2->print_asm(ctxt);
  // otherwise jump to statement 2 and then go to end
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
