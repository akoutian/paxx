// SPDX-License-Identifier: GPL-3.0-or-later

#include "info/info.hxx"

#include <iostream>

namespace paxx
{

cmn::command_status version()
{
    std::cout << "╭───────────────────────────────────────────╮\n";
    std::cout << "│    paxx: the C++ UNIX password manager    │\n";
    std::cout << "│                                           │\n";
    std::cout << "│                   v0.0.1                  │\n";
    std::cout << "╰───────────────────────────────────────────╯" << std::endl;

    return {};
}

cmn::command_status help()
{
    version();

    std::cout << "\n";
    std::cout << "Usage:\n";
    std::cout << "    paxx show [--qrcode, -q] [--line=line-number, --line "
                 "line-number, -l=line-number, -l line-number, -lline-number] pass-name\n";
    std::cout
        << "        show existing password and optionally  print it on the console as a QR code.\n";
    std::cout << "    paxx rm [--recursive,-r] [--force,-f] pass-name\n";
    std::cout << "        remove existing password or directory, optionally forcefully.\n";
    std::cout << "    paxx help\n";
    std::cout << "        show this text.\n";
    std::cout << "    paxx version\n";
    std::cout << "        show version information." << std::endl;

    return {};
}

} // namespace paxx
