#ifndef MPM_MPL_HPP_
#define MPM_MPL_HPP_

#include <type_traits>

namespace mpm
{

namespace mpl
{

template<typename H, typename... T>
struct or_ : std::conditional<H::value, std::true_type, or_<T...>>::type { };

template<typename H>
struct or_<H> : std::conditional<H::value, std::true_type, std::false_type>::type { };

template<typename H, typename... T>
struct and_ : std::conditional<H::value, and_<T...>, std::false_type>::type { };

template<typename H>
struct and_<H> : std::conditional<H::value, std::true_type, std::false_type>::type { };

template<typename T>
struct not_ : std::conditional<T::value, std::false_type, std::true_type> { };

}

}

#endif
