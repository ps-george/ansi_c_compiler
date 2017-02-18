#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_leaf.hpp"
#include "ast/ast_branch.hpp"
#include "ast/ast_list.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_iteration.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"


extern const Leaf *parseAST();

#endif
