// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.h"
#include "common/types.h"
#include "handle-args.h"

#include <iostream>

int main(int argc, char **argv)
{
    pass::cmn::parsed::Args parsed;
    pass::cmn::ready::Args ready;

    const auto result = pass::cli::BuildCli(parsed, ready).parse({argc, argv});

    if (!result)
    {
        std::cerr << "Error: " << result.message() << std::endl;
        return EXIT_FAILURE;
    }

    pass::cmn::Context ctx;
    pass::cli::HandleArgs(ready, ctx);

    if (ctx.status != 0 && ctx.message)
    {
        std::cerr << ctx.message.value() << std::endl;
    }

    return ctx.status;
}
