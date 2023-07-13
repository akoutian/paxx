// SPDX-License-Identifier: GPL-3.0-or-later

#include "handle-args.h"
#include "info/info.h"
#include "show/show.h"

namespace pass::cli
{

using pass::cmn::Context;

void Handle([[maybe_unused]] const cmn::HelpArgs &args, Context &ctx)
{
    pass::Help(ctx);
}

void Handle(const cmn::ShowArgs &args, Context &ctx)
{
    pass::Show(ctx, args);
}

void Handle([[maybe_unused]] const cmn::VersionArgs &args, Context &ctx)
{
    pass::Version(ctx);
}

void Handle([[maybe_unused]] std::monostate m, [[maybe_unused]] Context &ctx)
{
}

void HandleArgs(const cmn::ready::Args &args, Context &ctx)
{
    std::visit([&](auto &a) { Handle(a, ctx); }, args);
}

} // namespace pass::cli
