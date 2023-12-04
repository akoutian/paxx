// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.hxx"
#include "common/types.hxx"
#include "handle-args.hxx"

#include <iostream>

int main(int argc, char **argv)
{
    paxx::cmn::parsed::args parsed;
    paxx::cmn::ready::args ready;

    const auto result = paxx::cli::build_cli(parsed, ready).parse({argc, argv});

    if (!result)
    {
        std::cerr << "error: " << result.message() << std::endl;
        return EXIT_FAILURE;
    }

    const auto status = paxx::cli::handle_args(ready);

    if (status.message)
    {
        std::cerr << *status.message << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
