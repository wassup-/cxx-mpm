#include "variables.hpp"
#include "expressions.hpp"

#include <iostream>

using mpm::variables::a;
using mpm::variables::b;
using mpm::variables::x;
using mpm::variables::A;

int main(int, char**)
{
  constexpr auto expr = (a ^ a) * x + b ^ b;
  constexpr auto res = expr((a = 2), (b = 3), (x = 4));
  std::cout << expr << " = " << res << std::endl;
}
