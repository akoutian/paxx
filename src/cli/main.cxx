// SPDX-License-Identifier: GPL-3.0-or-later

#include "info/info.h"
#include "show/show.h"

#include <lyra/lyra.hpp>

#include <iostream>

namespace
{

struct Args
{
    bool help{};
    bool show{};
    bool version{};
};

auto BuildCli(Args &args)
{
    auto cli = lyra::cli();

    const auto help = [&]([[maybe_unused]] const lyra::group &g) { args.help = true; };
    cli |= lyra::opt(args.help).name("-h").name("--help");
    cli |= lyra::command("help", help);

    const auto show = [&]([[maybe_unused]] const lyra::group &g) { args.show = true; };
    cli |= lyra::command("show", show);

    const auto version = [&]([[maybe_unused]] const lyra::group &g) { args.version = true; };
    cli |= lyra::opt(args.version).name("-v").name("--version");
    cli |= lyra::command("version", version);

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

    if (args.show)
    {
        pass::Show();
        return EXIT_SUCCESS;
    }

    if (args.version)
    {
        pass::Version();
        return EXIT_SUCCESS;
    }

    pass::Show();

    return EXIT_SUCCESS;
}
