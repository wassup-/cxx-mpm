#include "variables.hpp"
#include "expressions.hpp"

#include <iostream>

namespace vars = mpm::variables;

int main(int, char**)
{
  constexpr auto expr = (vars::a * vars::a) * vars::x + vars::b;
  constexpr auto res = expr((vars::a = 1.3), (vars::b = 2), (vars::c = 1), (vars::x = 3.5));
  std::cout << expr << " = " << res << std::endl;
}
