// Copyright (C) 2022 Anastasios Koutian
// Distributed under the GNU GPL v3
// For full terms see the accompanying file COPYING

#include "info/info.h"

#include <lyra/lyra.hpp>

#include <iostream>

int main(int argc, char **argv)
{
    bool help = false;
    bool version = false;

    const auto cli = lyra::cli() | lyra::opt(help)["-h"]["--help"]("Show this text.") |
                     lyra::opt(version)["-v"]["--version"]("Show version information.");

    const auto result = cli.parse({argc, argv});

    if (!result)
    {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (help)
    {
        pass::Help();
        return EXIT_SUCCESS;
    }

    if (version)
    {
        pass::Version();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
