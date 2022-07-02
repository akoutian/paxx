// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/types.h"
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

    const auto help = [&]([[maybe_unused]] const auto &a) { args.help = true; };
    cli |= lyra::opt(args.help).name("-h").name("--help");
    cli |= lyra::command("help", help);

    const auto show = [&]([[maybe_unused]] const auto &a) { args.show = true; };
    cli |= lyra::command("show", show);

    const auto version = [&]([[maybe_unused]] const auto &a) { args.version = true; };
    cli |= lyra::opt(args.version).name("-v").name("--version");
    cli |= lyra::command("version", version);

    return cli;
}

void HandleArgs(const Args &args, pass::common::Info &info)
{
    if (args.help)
    {
        pass::Help(info);
    }

    if (args.show)
    {
        pass::Show(info);
    }

    if (args.version)
    {
        pass::Version(info);
    }

    pass::Show(info);
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

    pass::common::Info info;
    HandleArgs(args, info);

    if (info.status != 0)
    {
        std::cerr << "Something bad happened. TODO: print nice error messages here." << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
