#ifndef MPM_CONSTANT_HPP_
#define MPM_CONSTANT_HPP_

#include "impl.hpp"

#include <iostream>

namespace mpm
{

template<typename T>
struct constant
{
  constexpr constant(T v)
  : val(v)
  { }

  constexpr T value() const { return val; }

  friend std::ostream& operator<<(std::ostream& out, const constant& self)
  {
    return out << self.val;
  }

  const T val;
};

}

#endif
