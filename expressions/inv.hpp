#ifndef MPM_EXPRESSIONS_INV_HPP_
#define MPM_EXPRESSIONS_INV_HPP_

#include "../expression.hpp"
#include "../impl.hpp"
#include "../mpl.hpp"

namespace mpm
{

template<typename Expr>
struct Expr_inv : Expression<Expr_inv<Expr>>
{
  constexpr Expr_inv(Expr x)
  : expr(x)
  { }

  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(-::mpm::impl::cref_declval<Expr>()(args...))
  {
    return -expr(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const Expr_inv& self)
  {
    return out << '-' << self.expr;
  }

  Expr expr;
};

template<typename Expr>
struct is_expression<Expr_inv<Expr>> : std::true_type { };

template<typename Expr>
struct is_constant<Expr_inv<Expr>> : is_constant<Expr> { };

template<typename Expr>
struct is_variable<Expr_inv<Expr>> : is_variable<Expr> { };

}

#endif
