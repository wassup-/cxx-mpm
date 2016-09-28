#ifndef MPM_EXPRESSIONS_SIN_HPP_
#define MPM_EXPRESSIONS_SIN_HPP_

#include "../expression.hpp"
#include "../impl.hpp"
#include "../mpl.hpp"
#include "../mpm.hpp"

#include <cmath>

namespace mpm
{

namespace impl
{

template<typename, typename...>
struct lower_bound_impl;

template<typename Val, typename Prev, typename Next, typename... Rest>
struct lower_bound_impl<Val, Prev, Next, Rest...>
: std::conditional<(Next::index::value >= Val::value), Prev, lower_bound_impl<Val, Next, Rest...>> { };

template<typename, typename...>
struct upper_bound_impl;

template<typename Val, typename Prev, typename Next, typename... Rest>
struct upper_bound_impl<Val, Prev, Next, Rest...>
: std::conditional<(Next::index::value >= Val::value), Next, upper_bound_impl<Val, Next, Rest...>> { };

template<typename V, typename... Vs>
struct lower_bound : lower_bound_impl<V, Vs...>::type { };

template<typename V, typename... Vs>
struct upper_bound : upper_bound_impl<V, Vs...>::type { };

template<typename>
struct sine_lookup_table;

template<typename T>
struct sine_lookup_entry
{
  template<int Idx, T Val>
  struct e
  {
    using index = std::integral_constant<int, Idx>;
    using value = std::integral_constant<T, Val>;
  };
};

template<>
struct sine_lookup_table<int>
{
  using entry = sine_lookup_entry<int>;
  using table = mpl::type_sequence<entry::e<0, 0>, entry::e<2, 4>, entry::e<5, 10>, entry::e<7, 12>>;
};

template<typename T>
struct sin_solver
{
  struct lower_bound_not_found { };
  struct upper_bound_not_found { };

  template<typename Bound>
  constexpr static double solve(T v, Bound lb, Bound ub)
  {
    return Bound::value::value;
  }

  template<typename Lower, typename Upper>
  constexpr static double solve(T v, Lower lb, Upper ub)
  {
    using lower_bound = Lower;
    using upper_bound = Upper;
    using value_diff = mpl::diff<typename lower_bound::value, typename upper_bound::value>;
    using index_diff = mpl::diff<typename lower_bound::index, typename upper_bound::index>;
    return (lower_bound::value::value + ((v - lower_bound::index::value) * (value_diff::value / index_diff::value)));
  }

  template<typename Lower, typename Head>
  constexpr static double solve_ub(T v, Lower lb, mpl::type_sequence<Head>)
  {
    return (Head::index::value >= v)
           ? solve(v, lb, Head{})
           : throw upper_bound_not_found{};
  }

  template<typename Lower, typename Head, typename Next, typename... Tail>
  constexpr static double solve_ub(T v, Lower lb, mpl::type_sequence<Head, Next, Tail...>)
  {
    using next_sequence = mpl::type_sequence<Next, Tail...>;
    return (Head::index::value >= v)
           ? solve(v, lb, Head{})
           : solve_ub(v, lb, next_sequence{});
  }

  template<typename Head>
  constexpr static double solve_lb(T v, mpl::type_sequence<Head>)
  {
    using next_sequence = mpl::type_sequence<Head>;
    return (Head::index::value <= v)
           ? solve_ub(v, Head{}, next_sequence{})
           : throw lower_bound_not_found{};
  }

  template<typename Head, typename Next, typename... Tail>
  constexpr static double solve_lb(T v, mpl::type_sequence<Head, Next, Tail...>)
  {
    using next_sequence = mpl::type_sequence<Next, Tail...>;
    return (Next::index::value >= v)
           ? solve_ub(v, Head{}, next_sequence{})
           : solve_lb(v, next_sequence{});
  }

  constexpr double operator()(T v) const
  {
    using lookup_table = typename sine_lookup_table<T>::table;
    return solve_lb(v, lookup_table{});
  }
};

} // namespace impl

template<typename Expr>
struct Expr_sin : Expression<Expr_sin<Expr>>
{
  constexpr Expr_sin(Expr x)
  : expr(x)
  { }

  template<typename... Args>
  constexpr double operator()(Args... args) const
  {
    return impl::sin_solver<decltype(expr(args...))>()(expr(args...));
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_sin& self)
  {
    return out << "sin(" << self.expr << ")";
  }

  Expr expr;
};

template<typename Expr>
struct is_expression<Expr_sin<Expr>> : std::true_type { };

template<typename Expr>
struct is_constant<Expr_sin<Expr>> : is_constant<Expr> { };

template<typename Expr>
struct is_variable<Expr_sin<Expr>> : is_variable<Expr> { };

template<typename Expr>
constexpr Expr_sin<typename mpm_expression<Expr>::type>
sin(Expr x)
{
  return { x };
}

} // namespace mpm

#endif
