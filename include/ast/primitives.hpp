#ifndef AST_PRIMITIVE_HPP_
#define AST_PRIMITIVE_HPP_

#include "ast_node.hpp"
#include "ast_list.hpp"
#include "ast_expression.hpp"

// Primitives
class StringLiteral : public Expression {};

//! Abstract base class for constant
class Constant : public Expression {};

class FloatConstant : public Constant {};

class IntConstant : public Constant {};

//! An identifier, check identifier list for definition.
//! Enum is of type int.
class EnumConstant : public Constant {};

class CharConstant : public Constant {};


#endif
