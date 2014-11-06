#include "variables.hpp"
#include "expressions.hpp"

#include <iostream>

using mpm::variables::a;
using mpm::variables::b;
using mpm::variables::c;
using mpm::variables::_;

int main(int, char**)
{
  constexpr auto expr = sin(a);
  constexpr auto res = expr((a = 1));
  std::cout << make_expression_printer(expr) << " = " << res << std::endl;
}
