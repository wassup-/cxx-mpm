#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <type_traits>

template<typename T>
using not_ = std::integral_constant<bool, !T::value>;

template<typename T, typename U>
using enable_if = std::enable_if<T::value, U>;

template<typename T, typename U = void>
using enable_if_t = typename enable_if<T, U>::type;

template<typename T, typename True, typename False>
using conditional = std::conditional<T::value, True, False>;

template<typename T, typename True, typename False>
using conditional_t = typename conditional<T, True, False>::type;

#endif
