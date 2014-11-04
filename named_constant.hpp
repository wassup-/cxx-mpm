#ifndef MPM_NAMED_CONSTANT_HPP_
#define MPM_NAMED_CONSTANT_HPP_

#include "constant.hpp"

namespace mpm
{

template<char Name, typename T>
struct Named_constant : Constant<T>
{
  using Constant<T>::Constant;

  constexpr char name() const { return Name; }
};

}

#endif
