// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/types.h"
#include "info/info.h"
#include "show/show.h"

#include <lyra/lyra.hpp>

#include <iostream>

namespace
{

using pass::cmn::Info;

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

void HandleArgs(const Args &args, Info &info)
{
    if (args.help)
    {
        pass::Help(info);
        return;
    }

    if (args.show)
    {
        pass::Show(info);
        return;
    }

    if (args.version)
    {
        pass::Version(info);
        return;
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

    Info info;
    HandleArgs(args, info);

    if (info.status != 0 && info.message)
    {
        std::cerr << info.message.value() << std::endl;
    }

    exit(info.status);
}
