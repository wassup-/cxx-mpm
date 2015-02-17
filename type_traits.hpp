#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <type_traits>

template<typename T>
using _t = typename T::type;

template<typename T>
using not_ = std::integral_constant<bool, !T::value>;

template<typename T, typename U>
using enable_if = std::enable_if<T::value, U>;

template<typename T, typename U = void>
using enable_if_t = _t<enable_if<T, U>>;

template<typename T, typename True, typename False>
using conditional = std::conditional<T::value, True, False>;

template<typename T, typename True, typename False>
using conditional_t = _t<conditional<T, True, False>>;

#endif
