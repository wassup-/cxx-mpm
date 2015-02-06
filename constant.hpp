#ifndef MPM_CONSTANT_HPP_
#define MPM_CONSTANT_HPP_

#include "impl.hpp"
#include "predefs.hpp"

#include <iostream>

namespace mpm
{

template<typename T>
struct Constant
{
  constexpr Constant(T v)
  : val{ v }
  { }

  constexpr T value() const { return val; }

  template<typename... Args>
  constexpr T operator()(Args... args) const { return value(); }

  friend std::ostream& operator<<(std::ostream& out, const Constant& self)
  {
    return out << self.val;
  }

  const T val;
};

template<typename T>
struct is_constant<Constant<T>> : std::true_type { };

template<typename T>
struct is_expression<Constant<T>> : std::true_type { };

} // namespace mpm

#endif
