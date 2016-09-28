#ifndef MPM_EXPRESSIONS_POW_HPP_
#define MPM_EXPRESSIONS_POW_HPP_

#include "../expression.hpp"
#include "../impl.hpp"
#include "../mpl.hpp"

namespace mpm
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

} // namespace impl

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

template<typename Left, typename Right>
struct is_expression<Expr_pow<Left, Right>> : std::true_type { };

template<typename Left, typename Right>
struct is_constant<Expr_pow<Left, Right>> : mpl::and_<is_constant<Left>, is_constant<Right>> { };

template<typename Left, typename Right>
struct is_variable<Expr_pow<Left, Right>> : mpl::or_<is_variable<Left>, is_variable<Right>> { };

template<typename Left, typename Right>
constexpr expression_t<Expr_pow, Left, Right>
operator^(Left l, Right r)
{
  return { l, r };
}

template<typename Left, typename Right>
constexpr expression_t<Expr_pow, Left, Right>
pow(Left l, Right r)
{
  return { l, r };
}

} // namespace mpm

#endif
