// SPDX-License-Identifier: GPL-3.0-or-later

#include "handle-args.hxx"
#include "info/info.hxx"
#include "remove/remove.hxx"
#include "show/show.hxx"

namespace paxx::cli
{

using paxx::cmn::context;

void handle([[maybe_unused]] const cmn::help_args &args, context &ctx)
{
    paxx::help(ctx);
}

void handle(const cmn::show_args &args, context &ctx)
{
    paxx::show(ctx, args);
}

void handle([[maybe_unused]] const cmn::version_args &args, context &ctx)
{
    paxx::version(ctx);
}

void handle(const cmn::remove_args &args, context &ctx)
{
    paxx::remove(ctx, args);
}

void handle([[maybe_unused]] std::monostate m, [[maybe_unused]] context &ctx)
{
}

void handle_args(const cmn::ready::args &args, context &ctx)
{
    std::visit([&](auto &a) { handle(a, ctx); }, args);
}

} // namespace paxx::cli
