// SPDX-License-Identifier: GPL-3.0-or-later

#include "cli.hxx"
#include "handle-args.hxx"

#include <iostream>

int main(int argc, char **argv)
{
    paxx::cli::cli cli;

    const auto result = cli.parse(argc, argv);

    if (!result)
    {
        std::cerr << "error: " << result.message() << std::endl;
        return EXIT_FAILURE;
    }

    const auto status = paxx::cli::handle_args(cli.get());

    if (status.message)
    {
        std::cerr << *status.message << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
