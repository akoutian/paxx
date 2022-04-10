#include "info/info.h"

#include <iostream>

namespace pass
{

void Version()
{
    std::cout << "+--------------------------------------------+\n";
    std::cout << "| pass++: the standard unix password manager |\n";
    std::cout << "|                                            |\n";
    std::cout << "|                  C++ port                  |\n";
    std::cout << "|                                            |\n";
    std::cout << "|                   v0.0.1                   |\n";
    std::cout << "+--------------------------------------------+" << std::endl;
}

void Help()
{
    Version();

    std::cout << "\n";
    std::cout << "Usage:\n";
    std::cout << "    pass++ help\n";
    std::cout << "        Show this text.\n";
    std::cout << "    pass++ version\n";
    std::cout << "        Show version information." << std::endl;
}

} // namespace pass
