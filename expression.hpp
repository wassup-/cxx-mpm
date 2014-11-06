#ifndef MPM_EXPRESSION_HPP_
#define MPM_EXPRESSION_HPP_

#include "impl.hpp"
#include "predefs.hpp"

#include <iostream>

namespace mpm
{

template<typename Derived>
struct Expression
{
  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(impl::cref_declval<Derived>()(args...))
  {
    return static_cast<const Derived&>(*this)(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expression& self)
  {
    return out << static_cast<const Derived&>(self);
  }
};

template<typename T>
struct is_constant<Expression<T>> : is_constant<T> { };

template<typename T>
struct is_expression<Expression<T>> : std::true_type { };

template<typename T>
struct is_named<Expression<T>> : is_named<T> { };

template<typename T>
struct is_variable<Expression<T>> : is_variable<T> { };

namespace printers
{

template<typename Expression>
struct expression_printer
{
  constexpr expression_printer(Expression e)
  : expr(e)
  { }

  void print_expression(std::ostream& out, std::true_type) const
  {
    out << expr.name();
  }

  void print_expression(std::ostream& out, std::false_type) const
  {
    out << expr;
  }

  friend std::ostream& operator<<(std::ostream& out, const expression_printer& self)
  {
    self.print_expression(out, mpm::is_named<Expression>{});
    return out;
  }

  Expression expr;
};

}

template<typename Expression, typename = typename std::enable_if<is_expression<Expression>::value>::type>
constexpr printers::expression_printer<Expression> make_expression_printer(Expression expr)
{
  return { expr };
}

}

#endif
