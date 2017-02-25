#ifndef AST_HPP_
#define AST_HPP_

#include "ast/node.hpp"
#include "ast/variable.hpp"
#include "ast/constant.hpp"
#include "ast/expression.hpp"
#include "ast/unary_expression.hpp"
#include "ast/binary_expression.hpp"
#include "ast/list.hpp"
#include "ast/declaration.hpp"
#include "ast/statement.hpp"
#include "ast/function.hpp"
#include "ast/iteration_statement.hpp"
#include "ast/jump_statement.hpp"
#include "ast/labeled_statement.hpp"
#include "ast/selection_statement.hpp"


extern const Node *parseAST();

#endif
