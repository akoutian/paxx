// SPDX-License-Identifier: GPL-3.0-or-later

#include "info/info.h"

#include <iostream>

namespace pass
{

void Version([[maybe_unused]] cmn::Context &ctx)
{
    std::cout << "╭───────────────────────────────────────────╮\n";
    std::cout << "│    paxx: the C++ UNIX password manager    │\n";
    std::cout << "│                                           │\n";
    std::cout << "│                   v0.0.1                  │\n";
    std::cout << "╰───────────────────────────────────────────╯" << std::endl;
}

// TODO: rename "pass" to "paxx" here
void Help([[maybe_unused]] cmn::Context &ctx)
{
    Version(ctx);

    std::cout << "\n";
    std::cout << "Usage:\n";
    std::cout << "    pass rm [--recursive,-r] [--force,-f] pass-name\n";
    std::cout << "        Remove existing password or directory, optionally forcefully.\n";
    std::cout << "    pass help\n";
    std::cout << "        Show this text.\n";
    std::cout << "    pass version\n";
    std::cout << "        Show version information." << std::endl;
}

} // namespace pass
