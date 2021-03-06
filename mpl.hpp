#ifndef MPM_MPL_HPP_
#define MPM_MPL_HPP_

#include <type_traits>

namespace mpm
{

namespace mpl
{

template<typename H, typename... T>
struct and_ : conditional_t<H, and_<T...>, std::false_type> { };

template<typename H>
struct and_<H> : conditional_t<H, std::true_type, std::false_type> { };

template<typename H, typename... T>
struct or_ : conditional_t<H, std::true_type, or_<T...>> { };

template<typename H>
struct or_<H> : conditional_t<H, std::true_type, std::false_type> { };

template<typename T>
struct not_ : conditional_t<T, std::false_type, std::true_type> { };

template<typename...> struct type_sequence { };
template<typename T, T...> struct integer_sequence { };

template<typename T, typename U>
struct diff
: std::integral_constant<decltype(T::value - U::value), (T::value - U::value)> { };

namespace impl
{

template<typename, typename...>
struct lower_bound_impl;

template<typename Val, typename Prev, typename Cur, typename Next, typename... Rest>
struct lower_bound_impl<Val, Prev, Cur, Next, Rest...>
: std::conditional<(Next::value >= Cur::value), Prev, lower_bound_impl<Val, Cur, Next, Rest...>> { };

template<typename, typename...>
struct upper_bound_impl;

template<typename Val, typename Prev, typename Cur, typename Next, typename... Rest>
struct upper_bound_impl<Val, Prev, Cur, Next, Rest...>
: std::conditional<(Next::value >= Cur::value), Next, upper_bound_impl<Val, Cur, Next, Rest...>> { };

} // namespace impl

template<typename V, typename... Vs>
struct lower_bound : impl::lower_bound_impl<V, Vs...>::type { };

template<typename V, typename... Vs>
struct upper_bound : impl::upper_bound_impl<V, Vs...>::type { };

} // namespace mpl

} // namespace mpm

#endif
