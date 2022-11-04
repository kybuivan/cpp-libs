#include <iostream>
#include <string>
#include "twin_config.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << twin_VERSION_MAJOR << "."
                << twin_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    std::string orbits ("365.24 29.53");
    std::string::size_type sz;     // alias of size_t

    double earth = std::stod (orbits,&sz);
    double moon = std::stod (orbits.substr(sz));
    std::cout << "The moon completes " << (earth/moon) << " orbits per Earth year.\n";
    return 0;
}