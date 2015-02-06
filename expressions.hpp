#ifndef MPM_EXPRESSIONS_HPP_
#define MPM_EXPRESSIONS_HPP_

#include "expression.hpp"
#include "impl.hpp"
#include "mpl.hpp"
#include "type_traits.hpp"

#include <iostream>

namespace mpm
{

// Helper struct for making anything a valid expression
template<typename T>
struct mpm_expression
{
  using type = conditional_t<is_expression<T>, T, Constant<T>>;

  constexpr mpm_expression(type x)
  : expr{ x }
  { }

  type expr;
};

template<template<typename, typename> class expr, typename Left, typename Right>
struct as_expression
{
  using type = expr<typename mpm_expression<Left>::type, typename mpm_expression<Right>::type>;
};

template<template<typename, typename> class Expr, typename Left, typename Right>
using expression_t = typename as_expression<Expr, Left, Right>::type;

} // namespace mpm

#include "expressions/add.hpp"
#include "expressions/div.hpp"
#include "expressions/eq.hpp"
#include "expressions/inv.hpp"
#include "expressions/mul.hpp"
#include "expressions/neq.hpp"
#include "expressions/pow.hpp"
#include "expressions/sin.hpp"
#include "expressions/sub.hpp"

#endif
