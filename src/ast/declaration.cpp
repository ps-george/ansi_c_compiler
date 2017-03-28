/*
 * declaration.cpp
 *
 *
 */

#include "iostream"
#include "codegen_helpers.hpp"
#include "ast/declaration.hpp"
#include "ast/variable.hpp"

/*
 * GETTERS
 */
std::string Declarator::getNodeType() const { return "Declarator"; };
std::string InitDeclarator::getNodeType() const { return "InitDeclarator"; };
std::string ArrayDeclarator::getNodeType() const { return "ArrayDeclarator"; };
std::string FunctionDeclarator::getNodeType() const { return "FunctionDeclarator"; };
std::string Declaration::getNodeType() const { return "Declaration"; };

std::string Declaration::getId() const {
  return dlist->getChildren()[0]->getId();
}

std::string Declaration::getTypename() const {
  return type->getTypename();
};

std::vector<std::string> Declaration::getTypeVec() const {
  return type->getTypeVec();
};

//!
std::vector<const Node *> InitDeclarator::getChildren() const {
  std::vector<const Node *> v = Declarator::getChildren();
  v.push_back(e);
  return v;
}

//! Cut out the middle man
std::vector<const Node *> Declaration::getChildren () const {
  // for each item in dlist
  // std::cerr << "Finding children of declaration" << std::endl;
  return dlist->getChildren();
}

void Declarator::setChildDefs() const {
  childDefs.push_back(getId());
}

std::vector<std::string> Declaration::getChildDefs() const {
 return childDefs;
}

const List * FunctionDeclarator::getParams() const {
  return p;
}

/*
 *  END OF GETTERS
 */

//! Setter
void Declaration::setChildDefs() const {
  // For each of then declarators that are children of this
  for (auto &it : getChildren()){
    it->setChildDefs();
    std::vector<std::string> tmp = it->getChildDefs(); // Sets the metadata by getting the childDefs of it's children
    childDefs.insert(childDefs.end(), tmp.begin(), tmp.end());
  }
}

void ArrayDeclarator::setChildDefs() const {
  std::string id = getId();
  childDefs.push_back(id);
  if (e->getNodeType()=="IntConstant"){
    std::cerr << e->getId() << std::endl;
    int val = std::stoi(e->getId(),0,0);
    for (int i = 0; i<val;i++){
      childDefs.push_back(id+"["+std::to_string(i)+"]");
    }
  }
}

/*
 * PRINT_ASM
 */

// Something has been declared
Context Declaration::print_asm(Context ctxt, int d) const{
  // This works for shadowing, but not for InitDeclarators
  // ctxt.ss() << "## " << getNodeType() << std::endl;
  if (dlist->getChildren().size()){
    for (auto &it : dlist->getChildren()){
      std::string id = it->getId();
      ctxt.ss() << "## " << it->getNodeType() << ", " << id << ", " << it->getPtr() << std::endl;
      
      ctxt.ss() << "# assign variable " << id << std::endl;
      if (it->getPtr()){
        ctxt.assignVariable(id, type->getTypename(),0,1);
        int offset = ctxt.getVarOffset(id);
        ctxt.ss() << "\taddiu\t$8,$fp," << offset + 4 << std::endl;
        ctxt.ss() << "\tsw\t$8," << offset << "($fp)" << std::endl;
      }
      else{
        ctxt.assignVariable(id, type->getTypename());
      }
      //! \todo this is a hack to get InitDeclarator to work, could be more graceful
      if (it->getNodeType()=="InitDeclarator"){
        it->print_asm(ctxt);
      }
    }
  }
  return ctxt;
}

Context Declarator::print_asm(Context ctxt, int d) const{
  // ctxt.ss() << "## " << getNodeType() << std::endl;
  return ctxt;
}

Context InitDeclarator::print_asm(Context ctxt, int d) const{
  e->print_asm(ctxt);
  if (getPtr()){
    ctxt.ss() << "# hi " << std::endl;
    ctxt.setVarPtr(getId());
  }
  ctxt.storeVariable(getId());
  return ctxt;
}

//Context Declarator::print_asm(Context ctxt, int d) const {
//
//}

/* PRINT XML */
void Declarator::print_xml(std::ostream &stream) const{
  if (!parser){
    tab(stream,true);
    stream << getHeader() << std::endl;
  }
  child->print_xml(stream);
  if (!parser){
    tab(stream,false);
    stream << getFooter() << std::endl; 
  }
}

void FunctionDeclarator::print_xml(std::ostream &stream) const {
  // For each of the parameters, print out the parameter
  for (auto &it : p->getChildren()) {
    if (parser){
      for (auto &d : it->getChildren()) {
        tab(stream);
        stream << "<Parameter id=\"" << d->getId() << "\" type=\"" << ((const Declaration *)it)->getTypename() << "\" " << d->getDeets() << " />" << std::endl;
      }
    }
    else {
      it->print_xml(stream);
    }
  }
};

void Declaration::print_xml(std::ostream &stream) const{
  if (!parser){
    tab(stream,true);
    stream << getHeader() << std::endl;
  }
  dlist->print_xml(stream);
  if (!parser){
    tab(stream,false);
    stream << getFooter() << std::endl; 
  }
};
/* END OF PRINT XML */












/* PRINT C */
// void Declarator::print_c() const { 
//  child->print_c();
//}

//void FunctionDeclarator::print_c() const {
//  // For each of the parameters, print out the parameters
//  // std::cout << "/* "<< getNodeType() << "*/";
//  std::cout << getId() << "(";
//  bool first = true;
//  for (auto &it : p->getChildren()) {
//    if (!first){
//      std::cout << ", ";
//    }
//    first = false;
//    it->print_c();
//  }
//  std::cout << ")";
//};
//
//void Declaration::print_c() const{
//  tab();
//  std::cout << type->getTypename() << " ";
//  bool first = true;
//  for (auto &it : dlist->getChildren()) {
//    if (!first){
//      std::cout << ", ";
//    }
//    first = false;
//    it->print_c();
//  }
//  // std::cout << "/* "<< getNodeType() << "*/" << std::endl;
//};
//
