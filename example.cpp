#include "variables.hpp"
#include "expressions.hpp"

#include <iostream>

using mpm::variables::a;
using mpm::variables::b;
using mpm::variables::c;

int main(int, char**)
{
  constexpr auto expr = (a = b + c);
  constexpr auto res = expr((b = 1), (c = 2));

  std::cout << make_expression_printer(expr) << " = " << res << std::endl;
}
