#ifndef MPM_IMPL_HPP_
#define MPM_IMPL_HPP_

#include <type_traits>

namespace mpm
{

template<char, typename> struct Named_constant;

namespace impl
{

template<typename T> struct identity { using type = T; };

template<char> struct variable_not_set { };

template<char Name, typename...>
struct result_type_impl
: identity<variable_not_set<Name>> { };

template<char Name, typename T, typename... R>
struct result_type_impl<Name, Named_constant<Name, T>, R...>
: identity<T> { };

template<char Name, typename H, typename... T>
struct result_type_impl<Name, H, T...>
: result_type_impl<Name, T...> { };

template<char Name, typename... T>
struct result_type : result_type_impl<Name, T...> { };

template<int, char Name, typename...>
struct find_named_impl
: identity<variable_not_set<Name>> { };

template<int Idx, char Name, typename T, typename... R>
struct find_named_impl<Idx, Name, Named_constant<Name, T>, R...>
: identity<std::integral_constant<int, Idx>> { };

template<int Idx, char Name, typename H, typename... T>
struct find_named_impl<Idx, Name, H, T...>
: find_named_impl<(Idx + 1), Name, T...> { };

template<char Name, typename... T>
struct find_named
: find_named_impl<0, Name, T...> { };

template<typename T>
const T& cref_declval();

}

}

#endif
