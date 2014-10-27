#ifndef MPM_VARIABLE_HPP_
#define MPM_VARIABLE_HPP_

#include "impl.hpp"
#include "named_constant.hpp"

#include <iostream>
#include <tuple>

namespace mpm
{

template<char Name>
struct variable
{
  template<typename... NamedVars>
  constexpr typename impl::result_type<Name, NamedVars...>::type operator()(NamedVars... vars) const
  {
    using index = impl::find_named<Name, NamedVars...>;
    return std::get<index::value>(std::make_tuple(vars...)).value();
  }

  template<typename T>
  constexpr named_constant<Name, T> operator=(T v) const
  {
    return { v };
  }

  constexpr char name() const { return Name; }

  friend std::ostream& operator<<(std::ostream& out, const variable& self)
  {
    return out << self.name();
  }
};

}

#endif
