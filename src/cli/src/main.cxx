// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.hxx"
#include "common/types.hxx"
#include "handle-args.hxx"

#include <iostream>

int main(int argc, char **argv)
{
    paxx::cmn::parsed::Args parsed;
    paxx::cmn::ready::Args ready;

    const auto result = paxx::cli::BuildCli(parsed, ready).parse({argc, argv});

    if (!result)
    {
        std::cerr << "Error: " << result.message() << std::endl;
        return EXIT_FAILURE;
    }

    paxx::cmn::Context ctx;
    paxx::cli::HandleArgs(ready, ctx);

    if (ctx.status != 0 && ctx.message)
    {
        std::cerr << ctx.message.value() << std::endl;
    }

    return ctx.status;
}
