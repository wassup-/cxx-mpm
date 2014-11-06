#ifndef MPM_EXPRESSIONS_DIV_HPP_
#define MPM_EXPRESSIONS_DIV_HPP_

#include "../expression.hpp"
#include "../impl.hpp"
#include "../mpl.hpp"

namespace mpm
{

template<typename LExpr, typename RExpr>
struct Expr_div : Expression<Expr_div<LExpr, RExpr>>
{
  constexpr Expr_div(LExpr l, RExpr r)
  : left(l), right(r)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(::mpm::impl::cref_declval<LExpr>()(args...) + ::mpm::impl::cref_declval<RExpr>()(args...))
  {
    return left(args...) / right(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_div& self)
  {
    return out << self.left << " / " << self.right;
  }

  LExpr left;
  RExpr right;
};

template<typename Left, typename Right>
struct is_expression<Expr_div<Left, Right>> : std::true_type { };

template<typename Left, typename Right>
struct is_constant<Expr_div<Left, Right>> : mpl::and_<is_constant<Left>, is_constant<Right>> { };

template<typename Left, typename Right>
struct is_variable<Expr_div<Left, Right>> : mpl::or_<is_variable<Left>, is_variable<Right>> { };

template<typename Left, typename Right>
constexpr expression_t<Expr_div, Left, Right>
operator/(Left l, Right r)
{
  return { l, r };
}

}

#endif
