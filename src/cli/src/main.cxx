// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.h"
#include "common/types.h"
#include "handle-args.h"

#include <iostream>

int main(int argc, char **argv)
{
    pass::cli::parsed::Args parsed;
    pass::cli::ready::Args ready;

    const auto result = BuildCli(parsed, ready).parse({argc, argv});

    if (!result)
    {
        std::cerr << "Error: " << result.message() << std::endl;
        return EXIT_FAILURE;
    }

    pass::cmn::Context ctx;
    HandleArgs(ready, ctx);

    if (ctx.status != 0 && ctx.message)
    {
        std::cerr << ctx.message.value() << std::endl;
    }

    return ctx.status;
}
