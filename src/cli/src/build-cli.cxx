// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.h"

#include <lyra/lyra.hpp>

namespace pass::cli
{

void BuildHelp(lyra::cli &cli, cmn::parsed::Args &parsed, cmn::ready::Args &ready)
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

void BuildVersion(lyra::cli &cli, cmn::parsed::Args &parsed, cmn::ready::Args &ready)
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

void BuildShow(lyra::cli &cli, cmn::parsed::Args &parsed, cmn::ready::Args &ready)
{
    const auto makeReady = [&]([[maybe_unused]] auto g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.show;
        }
    };
    auto show = lyra::command("show", makeReady);
    auto ls = lyra::command("ls", makeReady);
    auto list = lyra::command("list", makeReady);

    const auto clipOpt = [&](size_t i)
    {
        parsed.show.outputType = cmn::OutputType::CLIPBOARD;
        parsed.show.line = i;
    };
    show.add_argument(lyra::opt(clipOpt, "clipVal").name("-c").name("--clip"));
    ls.add_argument(lyra::opt(clipOpt, "clipVal").name("-c").name("--clip"));
    list.add_argument(lyra::opt(clipOpt, "clipVal").name("-c").name("--clip"));

    const auto qrCodeOpt = [&](size_t i)
    {
        parsed.show.outputType = cmn::OutputType::QRCODE;
        parsed.show.line = i;
    };
    show.add_argument(lyra::opt(qrCodeOpt, "qrCodeVal").name("-q").name("--qrcode"));
    ls.add_argument(lyra::opt(qrCodeOpt, "qrCodeVal").name("-q").name("--qrcode"));
    list.add_argument(lyra::opt(qrCodeOpt, "qrCodeVal").name("-q").name("--qrcode"));

    const auto name = [&](std::string s) { parsed.show.name = s; };
    show.add_argument(lyra::arg(name, "name"));
    ls.add_argument(lyra::arg(name, "name"));
    list.add_argument(lyra::arg(name, "name"));

    cli.add_argument(show);
    cli.add_argument(ls);
    cli.add_argument(list);
}

lyra::cli BuildCli(cmn::parsed::Args &parsed, cmn::ready::Args &ready)
{
    auto cli = lyra::cli();

    BuildHelp(cli, parsed, ready);
    BuildVersion(cli, parsed, ready);
    BuildShow(cli, parsed, ready);

    return cli;
}

} // namespace pass::cli
