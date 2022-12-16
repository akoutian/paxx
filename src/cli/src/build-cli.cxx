// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.h"

#include <lyra/lyra.hpp>

namespace pass::cli
{

void BuildHelp(lyra::cli &cli, parsed::Args &parsed, ready::Args &ready)
{
    const auto makeReady = [&]([[maybe_unused]] const auto &g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.help;
        }
    };
    auto command = lyra::command("help", makeReady);

    cli.add_argument(command);
}

void BuildVersion(lyra::cli &cli, parsed::Args &parsed, ready::Args &ready)
{

    const auto makeReady = [&]([[maybe_unused]] const auto &g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.version;
        }
    };
    auto command = lyra::command("version", makeReady);

    cli.add_argument(command);
}

void BuildShow(lyra::cli &cli, parsed::Args &parsed, ready::Args &ready)
{
    const auto makeReady = [&]([[maybe_unused]] auto g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.show;
        }
    };
    auto command = lyra::command("show", makeReady);

    const auto clipOpt = [&](size_t i)
    {
        parsed.show.outputType = OutputType::CLIPBOARD;
        parsed.show.line = i;
    };
    command.add_argument(lyra::opt(clipOpt, "clipVal").name("-c").name("--clip"));

    const auto qrCodeOpt = [&](size_t i)
    {
        parsed.show.outputType = OutputType::QRCODE;
        parsed.show.line = i;
    };
    command.add_argument(lyra::opt(qrCodeOpt, "qrCodeVal").name("-q").name("--qrcode"));

    const auto name = [&](std::string s) { parsed.show.name = s; };
    command.add_argument(lyra::arg(name, "name"));

    cli.add_argument(command);
}

lyra::cli BuildCli(parsed::Args &parsed, ready::Args &ready)
{
    auto cli = lyra::cli();

    BuildHelp(cli, parsed, ready);
    BuildVersion(cli, parsed, ready);
    BuildShow(cli, parsed, ready);

    return cli;
}

} // namespace pass::cli
