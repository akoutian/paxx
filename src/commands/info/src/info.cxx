// SPDX-License-Identifier: GPL-3.0-or-later

#include "info/info.hxx"

#include <iostream>

namespace paxx
{

void Version([[maybe_unused]] cmn::Context &ctx)
{
    std::cout << "╭───────────────────────────────────────────╮\n";
    std::cout << "│    paxx: the C++ UNIX password manager    │\n";
    std::cout << "│                                           │\n";
    std::cout << "│                   v0.0.1                  │\n";
    std::cout << "╰───────────────────────────────────────────╯" << std::endl;
}

void Help([[maybe_unused]] cmn::Context &ctx)
{
    Version(ctx);

    std::cout << "\n";
    std::cout << "Usage:\n";
    std::cout << "    paxx show [--qrcode, -q] [--line=line-number, --line "
                 "line-number, -l=line-number, -l line-number, -lline-number] pass-name\n";
    std::cout
        << "        Show existing password and optionally  print it on the console as a QR code.\n";
    std::cout << "    paxx rm [--recursive,-r] [--force,-f] pass-name\n";
    std::cout << "        Remove existing password or directory, optionally forcefully.\n";
    std::cout << "    paxx help\n";
    std::cout << "        Show this text.\n";
    std::cout << "    paxx version\n";
    std::cout << "        Show version information." << std::endl;
}

} // namespace paxx
