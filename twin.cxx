#include <iostream>
#include <string>
#include <cmath>
#include "twin_config.h"
#ifdef USE_CORE
#include "twin_core.h"
#endif

int main(int argc, char *argv[])
{
    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << twin_VERSION_MAJOR << "."
                << twin_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    
    // convert input to double
    const double inputValue = std::stod(argv[1]);
    
#ifdef USE_CORE
    const double outputValue = core::sqrt(inputValue);
#else
    const double outputValue = std::sqrt(inputValue);
#endif
    std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
    return 0;
}