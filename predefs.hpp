#ifndef MPM_PREDEFS_HPP_
#define MPM_PREDEFS_HPP_

#include <type_traits>

namespace mpm
{

template<typename> struct is_constant : std::false_type { };
template<typename> struct is_expression : std::false_type { };
template<typename> struct is_named : std::false_type { };
template<typename> struct is_variable : std::false_type { };

} // namespace mpm

#endif
