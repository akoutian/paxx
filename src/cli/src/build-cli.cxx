// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.h"

#include <lyra/lyra.hpp>

namespace paxx::cli
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

    const auto clipOpt = [&]([[maybe_unused]] bool i)
    { parsed.show.outputType = cmn::OutputType::CLIPBOARD; };
    show.add_argument(lyra::opt(clipOpt).name("-c").name("--clip"));
    ls.add_argument(lyra::opt(clipOpt).name("-c").name("--clip"));
    list.add_argument(lyra::opt(clipOpt).name("-c").name("--clip"));

    const auto qrCodeOpt = [&]([[maybe_unused]] bool i)
    { parsed.show.outputType = cmn::OutputType::QRCODE; };
    show.add_argument(lyra::opt(qrCodeOpt).name("-q").name("--qrcode"));
    ls.add_argument(lyra::opt(qrCodeOpt).name("-q").name("--qrcode"));
    list.add_argument(lyra::opt(qrCodeOpt).name("-q").name("--qrcode"));

    const auto lineOpt = [&](size_t i) { parsed.show.line = i; };
    const auto hint = "line number";
    show.add_argument(lyra::opt(lineOpt, hint).name("-l").name("--line"));
    ls.add_argument(lyra::opt(lineOpt, hint).name("-l").name("--line"));
    list.add_argument(lyra::opt(lineOpt, hint).name("-l").name("--line"));

    const auto name = [&](std::string s) { parsed.show.name = s; };
    show.add_argument(lyra::arg(name, "name"));
    ls.add_argument(lyra::arg(name, "name"));
    list.add_argument(lyra::arg(name, "name"));

    cli.add_argument(show);
    cli.add_argument(ls);
    cli.add_argument(list);
}

void BuildDelete(lyra::cli &cli, cmn::parsed::Args &parsed, cmn::ready::Args &ready)
{
    const auto makeReady = [&]([[maybe_unused]] auto g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.del;
        }
    };
    auto rm = lyra::command("rm", makeReady);
    auto del = lyra::command("delete", makeReady);
    auto remove = lyra::command("remove", makeReady);

    const auto forceOpt = [&](bool i) { parsed.del.force = i; };
    rm.add_argument(lyra::opt(forceOpt).name("-f").name("--force"));
    del.add_argument(lyra::opt(forceOpt).name("-f").name("--force"));
    remove.add_argument(lyra::opt(forceOpt).name("-f").name("--force"));

    const auto recursiveOpt = [&](bool i) { parsed.del.recursive = i; };
    rm.add_argument(lyra::opt(recursiveOpt).name("-r").name("--recursive"));
    del.add_argument(lyra::opt(recursiveOpt).name("-r").name("--recursive"));
    remove.add_argument(lyra::opt(recursiveOpt).name("-r").name("--recursive"));

    const auto name = [&](std::string s) { parsed.del.name = s; };
    rm.add_argument(lyra::arg(name, "name"));
    del.add_argument(lyra::arg(name, "name"));
    remove.add_argument(lyra::arg(name, "name"));

    cli.add_argument(rm);
    cli.add_argument(del);
    cli.add_argument(remove);
}

lyra::cli BuildCli(cmn::parsed::Args &parsed, cmn::ready::Args &ready)
{
    auto cli = lyra::cli();

    BuildHelp(cli, parsed, ready);
    BuildVersion(cli, parsed, ready);
    BuildShow(cli, parsed, ready);
    BuildDelete(cli, parsed, ready);

    return cli;
}

} // namespace paxx::cli
