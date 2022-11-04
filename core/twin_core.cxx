#include "twin_core.h"
#include <iostream>
#include <cmath>

namespace core
{
    float sqrt(float input)
    {
#if defined(HAVE_LOG) && defined(HAVE_EXP)
    double result = std::exp(std::log(input) * 0.5);
    std::cout << "Computing sqrt of " << input << " to be " << result
                << " using log and exp" << std::endl;
#else
        double result = std::sqrt(result);
#endif
        return result;
    }
}
