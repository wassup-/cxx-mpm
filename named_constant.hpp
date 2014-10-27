#ifndef MPM_NAMED_CONSTANT_HPP_
#define MPM_NAMED_CONSTANT_HPP_

#include "constant.hpp"

namespace mpm
{

template<char Name, typename T>
struct named_constant : constant<T>
{
  using constant<T>::constant;

  constexpr char name() const { return Name; }
};

}

#endif
