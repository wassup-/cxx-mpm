#ifndef MPM_NAMED_EXPRESSION_HPP_
#define MPM_NAMED_EXPRESSION_HPP_

#include "expression.hpp"
#include "predefs.hpp"

namespace mpm
{

template<char Name, typename T>
struct Named_expression : T
{
  constexpr Named_expression(T x) : T(x) { }

  constexpr char name() const { return Name; }

  friend std::ostream& operator<<(std::ostream& out, const Named_expression& self)
  {
    return out << Name << " = " << static_cast<const T&>(self);
  }
};

template<char Name, typename T>
struct is_constant<Named_expression<Name, T>> : is_constant<T> { };

template<char Name, typename T>
struct is_expression<Named_expression<Name, T>> : std::true_type { };

template<char Name, typename T>
struct is_named<Named_expression<Name, T>> : std::true_type { };

template<char Name, typename T>
struct is_variable<Named_expression<Name, T>> : is_variable<T> { };

}

#endif
