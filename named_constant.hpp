#ifndef MPM_NAMED_CONSTANT_HPP_
#define MPM_NAMED_CONSTANT_HPP_

#include "constant.hpp"
#include "predefs.hpp"

namespace mpm
{

template<char Name, typename T>
struct Named_constant : Constant<T>
{
  using Constant<T>::Constant;

  constexpr char name() const { return Name; }
};

template<char Name, typename T>
struct is_constant<Named_constant<Name, T>> : std::true_type { };

template<char Name, typename T>
struct is_expression<Named_constant<Name, T>> : std::true_type { };

template<char Name, typename T>
struct is_named<Named_constant<Name, T>> : std::true_type { };

}

#endif
