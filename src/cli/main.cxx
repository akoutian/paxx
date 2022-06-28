// SPDX-License-Identifier: GPL-3.0-or-later

#include "info/info.h"

#include <lyra/lyra.hpp>

#include <iostream>

namespace
{

struct Args
{
    bool help{};
    bool version{};
};

auto BuildCli(Args &args)
{
    auto cli = lyra::cli();
    cli |= lyra::opt(args.help)["-h"]["--help"]("Show this text.");
    cli |= lyra::opt(args.version)["-v"]["--version"]("Show version information.");
    return cli;
}

} // namespace

int main(int argc, char **argv)
{
    Args args;
    const auto result = BuildCli(args).parse({argc, argv});

    if (!result)
    {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (args.help)
    {
        pass::Help();
        return EXIT_SUCCESS;
    }

    if (args.version)
    {
        pass::Version();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
