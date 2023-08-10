// SPDX-License-Identifier: GPL-3.0-or-later

#include "handle-args.hxx"
#include "delete/delete.hxx"
#include "info/info.hxx"
#include "show/show.hxx"

namespace paxx::cli
{

using paxx::cmn::Context;

void Handle([[maybe_unused]] const cmn::HelpArgs &args, Context &ctx)
{
    paxx::Help(ctx);
}

void Handle(const cmn::ShowArgs &args, Context &ctx)
{
    paxx::Show(ctx, args);
}

void Handle([[maybe_unused]] const cmn::VersionArgs &args, Context &ctx)
{
    paxx::Version(ctx);
}

void Handle(const cmn::DeleteArgs &args, Context &ctx)
{
    paxx::Delete(ctx, args);
}

void Handle([[maybe_unused]] std::monostate m, [[maybe_unused]] Context &ctx)
{
}

void HandleArgs(const cmn::ready::Args &args, Context &ctx)
{
    std::visit([&](auto &a) { Handle(a, ctx); }, args);
}

} // namespace paxx::cli
