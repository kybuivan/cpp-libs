#include "twin_core.h"
#include <iostream>
#include <cmath>
#include "mysqrt.h"

namespace core {
double sqrt(double x)
{
#ifdef USE_MYMATH
  return detail::mysqrt(x);
#else
  return std::sqrt(x);
#endif
}
}
