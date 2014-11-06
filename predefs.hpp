#ifndef MPM_PREDEFS_HPP_
#define MPM_PREDEFS_HPP_

namespace mpm
{

template<typename> struct is_constant : std::false_type { };
template<typename> struct is_expression : std::false_type { };
template<typename> struct is_named : std::false_type { };
template<typename> struct is_variable : std::false_type { };

}

#endif
