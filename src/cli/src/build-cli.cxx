// SPDX-License-Identifier: GPL-3.0-or-later

#include "build-cli.hxx"

#include <lyra/lyra.hpp>

namespace paxx::cli
{

void build_help(lyra::cli &cli, cmn::parsed::args &parsed, cmn::ready::args &ready)
{
    const auto make_ready = [&]([[maybe_unused]] const auto &g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.help;
        }
    };
    auto command = lyra::command("help", make_ready);

    cli.add_argument(command);
}

void build_version(lyra::cli &cli, cmn::parsed::args &parsed, cmn::ready::args &ready)
{

    const auto make_ready = [&]([[maybe_unused]] const auto &g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.version;
        }
    };
    auto command = lyra::command("version", make_ready);

    cli.add_argument(command);
}

void build_show(lyra::cli &cli, cmn::parsed::args &parsed, cmn::ready::args &ready)
{
    const auto make_ready = [&]([[maybe_unused]] auto g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.show;
        }
    };
    auto show = lyra::command("show", make_ready);
    auto ls = lyra::command("ls", make_ready);
    auto list = lyra::command("list", make_ready);

    const auto qr_code_opt = [&]([[maybe_unused]] bool i)
    { parsed.show.format = cmn::output_format::QRCODE; };
    show.add_argument(lyra::opt(qr_code_opt).name("-q").name("--qrcode"));
    ls.add_argument(lyra::opt(qr_code_opt).name("-q").name("--qrcode"));
    list.add_argument(lyra::opt(qr_code_opt).name("-q").name("--qrcode"));

    const auto line_opt = [&](size_t i) { parsed.show.line = i; };
    const auto hint = "line number";
    show.add_argument(lyra::opt(line_opt, hint).name("-l").name("--line"));
    ls.add_argument(lyra::opt(line_opt, hint).name("-l").name("--line"));
    list.add_argument(lyra::opt(line_opt, hint).name("-l").name("--line"));

    const auto name = [&](std::string s) { parsed.show.name = s; };
    show.add_argument(lyra::arg(name, "name"));
    ls.add_argument(lyra::arg(name, "name"));
    list.add_argument(lyra::arg(name, "name"));

    cli.add_argument(show);
    cli.add_argument(ls);
    cli.add_argument(list);
}

void build_remove(lyra::cli &cli, cmn::parsed::args &parsed, cmn::ready::args &ready)
{
    const auto make_ready = [&]([[maybe_unused]] auto g)
    {
        if (std::holds_alternative<std::monostate>(ready))
        {
            ready = parsed.del;
        }
    };
    auto rm = lyra::command("rm", make_ready);
    auto del = lyra::command("remove", make_ready);
    auto remove = lyra::command("remove", make_ready);

    const auto force_opt = [&](bool i) { parsed.del.force = i; };
    rm.add_argument(lyra::opt(force_opt).name("-f").name("--force"));
    del.add_argument(lyra::opt(force_opt).name("-f").name("--force"));
    remove.add_argument(lyra::opt(force_opt).name("-f").name("--force"));

    const auto recurse_opt = [&](bool i) { parsed.del.recursive = i; };
    rm.add_argument(lyra::opt(recurse_opt).name("-r").name("--recursive"));
    del.add_argument(lyra::opt(recurse_opt).name("-r").name("--recursive"));
    remove.add_argument(lyra::opt(recurse_opt).name("-r").name("--recursive"));

    const auto name = [&](std::string s) { parsed.del.name = s; };
    rm.add_argument(lyra::arg(name, "name"));
    del.add_argument(lyra::arg(name, "name"));
    remove.add_argument(lyra::arg(name, "name"));

    cli.add_argument(rm);
    cli.add_argument(del);
    cli.add_argument(remove);
}

lyra::cli build_cli(cmn::parsed::args &parsed, cmn::ready::args &ready)
{
    auto cli = lyra::cli();

    build_help(cli, parsed, ready);
    build_version(cli, parsed, ready);
    build_show(cli, parsed, ready);
    build_remove(cli, parsed, ready);

    return cli;
}

} // namespace paxx::cli
