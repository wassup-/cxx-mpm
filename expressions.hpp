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
struct Expr_add : Expression<Expr_add<LExpr, RExpr>>
{
  constexpr Expr_add(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_add& self)
  {
    return out << self.left << " + " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct Expr_sub : Expression<Expr_sub<LExpr, RExpr>>
{
  constexpr Expr_sub(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_sub& self)
  {
    return out << self.left << " - " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct Expr_mul : Expression<Expr_mul<LExpr, RExpr>>
{
  constexpr Expr_mul(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) * ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) * right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_mul& self)
  {
    return out << self.left << " * " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct Expr_div : Expression<Expr_div<LExpr, RExpr>>
{
  constexpr Expr_div(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_div& self)
  {
    return out << self.left << " / " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename LExpr, typename RExpr>
struct Expr_pow : Expression<Expr_pow<LExpr, RExpr>>
{
  constexpr Expr_pow(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return impl::pow(left(args...), right(args...));
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_pow& self)
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
                                         Constant<T>,
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
constexpr expression_t<expressions::Expr_add, Left, Right>
operator+(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::Expr_sub, Left, Right>
operator-(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::Expr_mul, Left, Right>
operator*(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::Expr_div, Left, Right>
operator/(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<expressions::Expr_pow, Left, Right>
operator^(Left l, Right r)
{
  return { l, r };
}

}

#endif
