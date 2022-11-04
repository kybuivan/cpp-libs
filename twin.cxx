#include <iostream>
#include <string>
#include "twin_config.h"
#ifdef USE_CORE
#include "twin_core.h"
#endif

int main(int argc, char *argv[])
{
    // report version
    std::cout << argv[0] << " Version " << twin_VERSION_MAJOR << "."
            << twin_VERSION_MINOR << std::endl;

    std::string orbits ("365.24 29.53");
    std::string::size_type sz;     // alias of size_t

    double earth = std::stod (orbits,&sz);
    double moon = std::stod (orbits.substr(sz));
#ifdef USE_CORE
    const double outputValue = core::sqrt(earth/moon);
#else
    const double outputValue = sqrt(earth/moon);
#endif
    std::cout << "The moon completes " << outputValue << " orbits per Earth year.\n";
    return 0;
}