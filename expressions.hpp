#ifndef MPM_EXPRESSIONS_HPP_
#define MPM_EXPRESSIONS_HPP_

#include "expression.hpp"
#include "impl.hpp"

#include <iostream>

namespace mpm
{

template<typename Left, typename Right>
struct expr_add : expression<expr_add<Left, Right>>
{
  constexpr expr_add(Left l, Right r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(impl::cref_declval<Left>()(args...) + impl::cref_declval<Right>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_add& self)
  {
    return out << self.left << " + " << self.right;
  }

  Left left;
  Right right;
};

template<typename Left, typename Right>
struct expr_sub : expression<expr_sub<Left, Right>>
{
  constexpr expr_sub(Left l, Right r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(impl::cref_declval<Left>()(args...) + impl::cref_declval<Right>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_sub& self)
  {
    return out << self.left << " - " << self.right;
  }

  Left left;
  Right right;
};

template<typename Left, typename Right>
struct expr_mul : expression<expr_mul<Left, Right>>
{
  constexpr expr_mul(Left l, Right r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(impl::cref_declval<Left>()(args...) * impl::cref_declval<Right>()(args...))
  {
    return left(args...) * right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_mul& self)
  {
    return out << self.left << " * " << self.right;
  }

  Left left;
  Right right;
};

template<typename Left, typename Right>
struct expr_div : expression<expr_div<Left, Right>>
{
  constexpr expr_div(Left l, Right r)
  : left(l), right(r)
  { }

  template<typename... Args>
  auto operator()(Args... args) const
  -> decltype(impl::cref_declval<Left>()(args...) + impl::cref_declval<Right>()(args...))
  {
    return left(args...) + right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expr_div& self)
  {
    return out << self.left << " / " << self.right;
  }

  Left left;
  Right right;
};

template<typename Left, typename Right>
constexpr expr_add<Left, Right> operator+(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expr_sub<Left, Right> operator-(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expr_mul<Left, Right> operator*(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expr_div<Left, Right> operator/(Left l, Right r)
{
  return { l, r };
}

}

#endif
