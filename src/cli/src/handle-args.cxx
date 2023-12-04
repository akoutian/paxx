// SPDX-License-Identifier: GPL-3.0-or-later

#include "handle-args.hxx"
#include "info/info.hxx"
#include "remove/remove.hxx"
#include "show/show.hxx"

namespace paxx::cli
{

cmn::command_status handle([[maybe_unused]] const cmn::help_args &args)
{
    return paxx::help();
}

cmn::command_status handle(const cmn::show_args &args)
{
    return paxx::show(args);
}

cmn::command_status handle([[maybe_unused]] const cmn::version_args &args)
{
    return paxx::version();
}

cmn::command_status handle(const cmn::remove_args &args)
{
    return paxx::remove(args);
}

cmn::command_status handle([[maybe_unused]] std::monostate m)
{
    return {};
}

cmn::command_status handle_args(const cmn::ready::args &args)
{
    return std::visit([&](auto &a) { return handle(a); }, args);
}

} // namespace paxx::cli
