#include "variables.hpp"
#include "expressions.hpp"
#include "inverse_expression.hpp"

#include <iostream>

using mpm::variables::a;
using mpm::variables::b;
using mpm::variables::c;
using mpm::variables::_;

template<typename Expression, char Name>
constexpr typename mpm::inverse_expression<Name, Expression>::type solve(Expression expr, mpm::Variable<Name> var)
{
  return { { } };
}

template<typename T>
void print_type(T)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename Expression, typename Result>
void print_result(Expression expr, Result res, std::true_type)
{
  std::cout << expr.name() << " = " << res;
}

template<typename Expression, typename Result>
void print_result(Expression expr, Result res, std::false_type)
{
  std::cout << expr << " = " << res;
}

template<typename Expression, typename Result>
void print_result(Expression expr, Result res)
{
  print_result(expr, res, std::false_type{});
}

int main(int, char**)
{
  constexpr auto expr = (a = b + c);
  constexpr auto res = expr((b = 4), (c = 1));
  print_result(expr, res);
  std::cout << std::endl;
}
