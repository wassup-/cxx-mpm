#ifndef MPM_VARIABLE_HPP_
#define MPM_VARIABLE_HPP_

#include "impl.hpp"
#include "named_constant.hpp"
#include "named_expression.hpp"
#include "predefs.hpp"

#include <iostream>
#include <tuple>

namespace mpm
{

template<char Name>
struct Variable
{
  template<typename... Args>
  constexpr typename impl::result_type<Name, Args...>::type operator()(Args... vars) const
  {
    using index = typename impl::find_named<Name, Args...>::type;
    return std::get<index::value>(std::make_tuple(vars...)).value();
  }

  template<typename T, typename = typename std::enable_if<!is_expression<T>::value>::type>
  constexpr Named_constant<Name, T> operator=(T v) const
  {
    return { v };
  }

  template<typename Expression, typename = typename std::enable_if<is_expression<Expression>::value>::type>
  constexpr Named_expression<Name, Expression> operator=(Expression x) const
  {
    return { x };
  }

  constexpr char name() const { return Name; }

  friend std::ostream& operator<<(std::ostream& out, const Variable& self)
  {
    return out << self.name();
  }
};

template<char Name>
struct is_expression<Variable<Name>> : std::true_type { };

template<char Name>
struct is_named<Variable<Name>> : std::true_type { };

template<char Name>
struct is_variable<Variable<Name>> : std::true_type { };

}

#endif
