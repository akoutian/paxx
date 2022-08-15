// SPDX-License-Identifier: GPL-3.0-or-later

#include "args.h"
#include "common/types.h"
#include "info/info.h"
#include "show/show.h"

#include <lyra/lyra.hpp>

#include <iostream>

namespace
{

using pass::cli::Args;
using pass::cmn::Context;

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

void HandleArgs(const Args &args, Context &ctx)
{
    if (args.help)
    {
        pass::Help(ctx);
        return;
    }

    if (args.show)
    {
        pass::Show(ctx);
        return;
    }

    if (args.version)
    {
        pass::Version(ctx);
        return;
    }

    pass::Show(ctx);
}

} // namespace

int main(int argc, char **argv)
{
    Args args;
    const auto result = BuildCli(args).parse({argc, argv});

    if (!result)
    {
        std::cerr << "Error: " << result.message() << std::endl;
        return EXIT_FAILURE;
    }

    Context ctx;
    HandleArgs(args, ctx);

    if (ctx.status != 0 && ctx.message)
    {
        std::cerr << ctx.message.value() << std::endl;
    }

    return ctx.status;
}
