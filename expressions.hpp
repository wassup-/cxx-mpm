#ifndef MPM_EXPRESSIONS_HPP_
#define MPM_EXPRESSIONS_HPP_

#include "expression.hpp"
#include "impl.hpp"

#include <iostream>

namespace mpm
{

namespace expressions
{

namespace impl
{

template<typename Base, typename Exp>
constexpr Base pow(Base base, Exp exp, Base result = 1)
{
  static_assert(std::is_integral<Exp>::value, "Exponent must be of integral type");
  return exp < 1 ? result
                 : pow(base * base, exp / 2, (exp % 2) ? result * base : result);
}

}

template<typename LExpr, typename RExpr>
struct expr_add : expression<expr_add<LExpr, RExpr>>
{
  constexpr expr_add(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_add& self)
  {
    return out << self.left << " + " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct expr_sub : expression<expr_sub<LExpr, RExpr>>
{
  constexpr expr_sub(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_sub& self)
  {
    return out << self.left << " - " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct expr_mul : expression<expr_mul<LExpr, RExpr>>
{
  constexpr expr_mul(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) * ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) * right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_mul& self)
  {
    return out << self.left << " * " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct expr_div : expression<expr_div<LExpr, RExpr>>
{
  constexpr expr_div(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_div& self)
  {
    return out << self.left << " / " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct expr_pow : expression<expr_pow<LExpr, RExpr>>
{
  constexpr expr_pow(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return impl::pow(left(args...), right(args...));
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_pow& self)
  {
    return out << self.left << "^" << self.right;
  }

  LExpr left;
  RExpr right;
};

}

template<typename T>
struct mpm_expression
{
  using type = typename std::conditional<std::is_arithmetic<T>::value,
                                         constant<T>,
                                         T>::type;

  constexpr mpm_expression(type x) : expr(x) { }

  type expr;
};

template<template<typename, typename> class expr, typename Left, typename Right>
struct as_expression
{
  using type = expr<typename mpm_expression<Left>::type, typename mpm_expression<Right>::type>;
};

template<template<typename, typename> class Expr, typename Left, typename Right>
using expression_t = typename as_expression<Expr, Left, Right>::type;

template<typename Left, typename Right>
constexpr expression_t<expressions::expr_add, Left, Right>
operator+(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::expr_sub, Left, Right>
operator-(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::expr_mul, Left, Right>
operator*(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::expr_div, Left, Right>
operator/(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::expr_pow, Left, Right>
operator^(Left l, Right r)
{
  return { l, r };
}

}

#endif
