// SPDX-License-Identifier: GPL-3.0-or-later

#include "handle-args.h"
#include "info/info.h"
#include "show/show.h"

namespace pass::cli
{

using pass::cmn::Context;

void Handle([[maybe_unused]] const HelpArgs &args, Context &ctx)
{
    pass::Help(ctx);
}

void Handle([[maybe_unused]] const ShowArgs &args, Context &ctx)
{
    pass::Show(ctx);
}

void Handle([[maybe_unused]] const VersionArgs &args, Context &ctx)
{
    pass::Version(ctx);
}

void Handle([[maybe_unused]] std::monostate m, [[maybe_unused]] Context &ctx)
{
}

void HandleArgs(const ready::Args &args, Context &ctx)
{
    std::visit([&](auto &a) { Handle(a, ctx); }, args);
}

} // namespace pass::cli
