#include <iostream>
#include <string>
#include "twin_config.h"
#include "twin_core.h"

int main(int argc, char *argv[])
{
    // report version
    std::cout << argv[0] << " Version " << twin_VERSION_MAJOR << "."
            << twin_VERSION_MINOR << std::endl;

    std::string orbits ("365.24 29.53");
    std::string::size_type sz;     // alias of size_t

    double earth = std::stod (orbits,&sz);
    double moon = std::stod (orbits.substr(sz));
    std::cout << "The moon completes " << core::sqrt(earth/moon) << " orbits per Earth year.\n";
    return 0;
}