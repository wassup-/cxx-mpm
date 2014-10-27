#ifndef MPM_EXPRESSION_HPP_
#define MPM_EXPRESSION_HPP_

#include "impl.hpp"

#include <iostream>

namespace mpm
{

template<typename Derived>
struct expression
{
public:
  template<typename... Args>
  constexpr auto operator()(Args... args) const
  -> decltype(impl::cref_declval<Derived>()(args...))
  {
    return static_cast<const Derived&>(*this)(args...);
  }

  friend std::ostream& operator<<(std::ostream& out, const expression& self)
  {
    return out << static_cast<const Derived&>(self);
  }
};

}

#endif
