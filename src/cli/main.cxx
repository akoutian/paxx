#include "info/info.h"

#include <iostream>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    pass::Version();
    pass::Help();

    return EXIT_SUCCESS;
}
