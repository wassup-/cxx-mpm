#ifndef MPM_INVERSE_EXPRESSION_HPP_
#define MPM_INVERSE_EXPRESSION_HPP_

#include "constant.hpp"
#include "expression.hpp"
#include "expressions.hpp"
#include "named_constant.hpp"
#include "variable.hpp"

namespace mpm
{

template<char, typename> struct inverse_expression;

template<char Name, typename Left, typename Right>
struct inverse_expression<Name, Expr_add<Left, Right>>
: impl::identity<Expr_sub<Left, Right>> { };

template<char Name, char Right>
struct inverse_expression<Name, Expr_add<Variable<Name>, Variable<Right>>>
: impl::identity<Expr_inv<Variable<Right>>> { };

template<char Name, char Left>
struct inverse_expression<Name, Expr_add<Variable<Left>, Variable<Name>>>
: impl::identity<Expr_inv<Variable<Left>>> { };

template<char Name, typename Left, typename Right>
struct inverse_expression<Name, Expr_sub<Left, Right>>
: impl::identity<Expr_add<Left, Right>> { };

template<char Name, typename Left, typename Right>
struct inverse_expression<Name, Expr_mul<Left, Right>>
: impl::identity<Expr_div<Left, Right>> { };

template<char Name, typename Left, typename Right>
struct inverse_expression<Name, Expr_div<Left, Right>>
: impl::identity<Expr_mul<Left, Right>> { };

template<char Name, typename T>
struct inverse_expression<Name, Expr_inv<T>>
: impl::identity<T> { };

template<char Name, typename T>
using inverse_expression_t = typename inverse_expression<Name, T>::type;

template<typename Expression, char Name>
constexpr inverse_expression_t<Name, Expression> solve_for(Expression expr, Variable<Name> var)
{
  return { { } };
}

}

#endif
