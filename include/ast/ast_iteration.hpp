#ifndef AST_ITERATION_HPP_
#define AST_ITERATION_HPP_

#include "ast_leaf.hpp"
#include "ast_branch.hpp"

#include <iostream>
#include <vector>
#include <string>

class Iteration : public Scope {
private:
public:
};

class WhileIteration : public Scope {
private:
  
public:
  WhileIteration(std::vector<const Leaf *> _stems) : Scope(_stems) {}
};

class DoWhileIteration : public Scope {
private:
  
public:
  DoWhileIteration(std::vector<const Leaf *> _stems) : Scope(_stems) {}
};

class ForIteration : public Scope {
private:
  
public:
  ForIteration(std::vector<const Leaf *> _stems) : Scope(_stems) {}
};

#endif
